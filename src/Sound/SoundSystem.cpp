/*
===========================================================================

Unkknow Engine Source Code

Copyright (C) 2014 BraXi.
All rights reserved.

This file is part of the Unkknow Engine Source Code ("Unkknow Engine Source Code").

Contact email: thebraxi@o2.pl
Contact website: http://www.braxi.org

===========================================================================
*/

#include "SoundSystem.h"
#include "../Engine.h"

#include <fstream>
#include <stdlib.h>

#include <AL/al.h>
#include <AL/alut.h>

// holds data for last loaded sound file
static ALint	load_sizeInBytes;
static ALint	load_channels;
static ALint	load_bits;
static ALint	load_frequency;

static ALfloat listenerPos[3];
static ALfloat listenerVel[3] = { 0.0,0.0,0.0 };
static ALfloat listenerRot[6] = { 0.0,0.0,1.0, 0.0,1.0,0.0 }; // {forward, up} // FIXME!


// =========================================================================== //
// =========================================================================== //

CSoundSystem::CSoundSystem()
{
}

CSoundSystem::~CSoundSystem()
{
}

// =========================================================================== //
// =========================================================================== //

bool CSoundSystem::Init()
{
	alutInit( NULL, NULL );

    int error = alGetError();
	if( error != AL_NO_ERROR )
	{
		PRINTF( "Sound System (OpenAL) initialization failed with error: %s\n", alutGetErrorString( error ) );
		return false;
	}

	listenerVolume = 0.1f;
	SoundFrame( 0.0 );

	LoadSound( "music" );

	PlaySound( "music", 1.0f, true );
	return true;
}

void CSoundSystem::Shutdown()
{
	FreeMemory();

	// Destroy OpenAL
	alutExit();
	PRINTF( "alut shutdown.\n" );
}


void CSoundSystem::FreeMemory()
{
	unsigned int i;

	for( i = 0; i < v_SndEnts.size(); i++ )
	{
		if( alIsSource( v_SndEnts[i]->source ) == AL_TRUE )
		{
			alSourceStop( v_SndEnts[i]->source );
			alDeleteSources( 1, &v_SndEnts[i]->source );
		}
		delete v_SndEnts[i];
	}
	v_SndEnts.clear();

	for( i = 0; i < v_Sounds.size(); i++ )
	{
		delete v_Sounds[i];
	}
	v_Sounds.clear();
}


// =========================================================================== //
// =========================================================================== //


void CSoundSystem::SoundFrame( double time, vec3 pos, vec3 rot )
{
	unsigned int 	i;
	SoundEnt		*ent;

	this->time = time;

	listenerPos[0] = (ALfloat)pos.x;
	listenerPos[1] = (ALfloat)pos.y;
	listenerPos[2] = (ALfloat)pos.z;


	alListenerf( AL_GAIN, listenerVolume );
    alListenerfv( AL_POSITION, listenerPos );
    alListenerfv( AL_VELOCITY, listenerVel );
    alListenerfv( AL_ORIENTATION, listenerRot );


updateSnd:

	for( i = 0; i < v_SndEnts.size(); i++ )
	{
		ent = v_SndEnts[i];

		if( !ent->looping && ent->endTime <= this->time || ent->endTime == 0.0 )
		{
			alSourceStop( ent->source );
			alDeleteSources( 1, &ent->source );
			delete ent;
			v_SndEnts.erase( v_SndEnts.begin() + i );
			goto updateSnd;
		}

		alSourcef( ent->source, AL_GAIN, ent->volume );
		alSourcei( ent->source, AL_LOOPING, ent->looping ? AL_TRUE : AL_FALSE );
//		alSource3f( ent->source, AL_POSITION, ent->origin.x, ent->origin.y, ent->origin.z );
		alSource3f( ent->source, AL_POSITION, listenerPos[0], listenerPos[1], listenerPos[2] );
	}

}




// =========================================================================== //
// =========================================================================== //


// =========================================================================== //
// =========================================================================== //


SoundEnt *CSoundSystem::PlaySound( std::string name, float volume, bool looping, vec3 origin )
{
	CSound			*snd;
	SoundEnt		*ent = NULL;

	if( !(snd = FindSound( name )) )
		return NULL;

	ent = new SoundEnt();

	if( !ent )
		return NULL;

	v_SndEnts.push_back( ent );

	ent->p_Snd = snd;
	ent->startTime = this->time;
	ent->endTime = ent->startTime + ent->p_Snd->duration;
	ent->volume = volume;
	ent->looping = looping;
	ent->origin = origin;

	if( alIsSource( ent->source ) != AL_TRUE )
	{
		alGenSources( 1, &ent->source );
	}

//		alSourceStop( ent->source );

	alSourcei( ent->source, AL_BUFFER, ent->p_Snd->buffer );							// bind sound
	alSourcei( ent->source, AL_LOOPING, ent->looping ? AL_TRUE : AL_FALSE );			// looping?
	alSourcef( ent->source, AL_GAIN, ent->volume );										// volume
	alSource3f( ent->source, AL_POSITION, ent->origin.x, ent->origin.y, ent->origin.z );// origin

	alSourcePlay( ent->source );

	return ent;
}


// =========================================================================== //
// =========================================================================== //

CSound *CSoundSystem::FindSound( std::string name )
{
	unsigned int i;

	for( i = 0; i < v_Sounds.size(); i++ )
	{
		if( name.compare( v_Sounds[i]->name ) == 0 )
			return v_Sounds[i];
	}
	return NULL;
}


CSound *CSoundSystem::LoadSound( std::string name )
{
	CSound 	*sound = NULL;

	sound = FindSound( name );
	if( sound != NULL )
		return sound;

	std::string fileName( GAME_DIR + "sound/" + name + ".wav" );

	ALuint sndBuf = alutCreateBufferFromFile( fileName.c_str() );
	if( !sndBuf  )
	{
		PRINTF( "%s not found or wrong format\n", fileName.c_str() );
		return NULL;
	}

	int error = alGetError();
	if( error != AL_NO_ERROR  )
	{
		PRINTF( "error %s during loading %s\n", alutGetErrorString( error ), fileName.c_str() );
		return NULL;
	}

	// get length
	alGetBufferi( sndBuf, AL_SIZE, &load_sizeInBytes );
	alGetBufferi( sndBuf, AL_CHANNELS, &load_channels );
	alGetBufferi( sndBuf, AL_BITS, &load_bits );
	alGetBufferi( sndBuf, AL_FREQUENCY, &load_frequency );

	int lengthInSamples = load_sizeInBytes * 8 / (load_channels * load_bits);
	double duration = ( (lengthInSamples / (float)load_frequency) ); // in seconds

	// create sound
	sound = new CSound();

	sound->name = name;
	sound->buffer = sndBuf;
	sound->duration = duration;

	v_Sounds.push_back( sound );

	PRINTF( "loaded: %s\n", fileName.c_str() );
	return sound;
}
