/*
===========================================================================

Unkknow Engine Source Code

Copyright (C) 2012-2013 BraXi.
All rights reserved.

This file is part of the Unkknow Engine Source Code ("Unkknow Engine Source Code").  

Contact email: thebraxi@o2.pl
Contact website: http://www.braxi.org

===========================================================================
*/


#ifndef _CSoundSystem_
#define _CSoundSystem_

#include "../Shared.h"
#include <vector>


typedef unsigned int ALuint;

#define MAX_SOUND_ENTITIES		256
#define MAX_CHANNEL_SOURCES		6


enum SoundStates
{
	SNDS_PLAY,
	SNDS_PAUSE,
	SNDS_STOP
};

enum SoundChannels
{
	SNDC_2D,
	SNDC_AMBIENT,
	SNDC_SFX,
	SNDC_WEAPON,
	SNDC_BODY,
	SNDC_NUM
};



////////////////////////////////////////////////////////////////////////

class CSound
{
public:
	std::string		name;
	unsigned int	buffer;		// aluint
	double			duration;	// length in seconds
};


// =========================================================================== //
// =========================================================================== //


class SoundEnt
{
public:
	SoundEnt() : p_Snd(NULL), origin(vec3(0)), volume(1.0f), looping(false), startTime(0.0) {}

	CSound			*p_Snd;
	vec3			origin;
	unsigned int	source;	

	float			volume;
	bool			looping;

	double			startTime, endTime;
};



// =========================================================================== //
// =========================================================================== //


class CSoundSystem
{
public:
	CSoundSystem();
	~CSoundSystem();

	bool						Init();
	void						Shutdown();
	void						FreeMemory();

	virtual void				SoundFrame( double time, vec3 pos = vec3(0,0,0), vec3 rot = vec3(0,0,0) );

	CSound 						*FindSound( std::string name );
	CSound						*LoadSound( std::string name );

	void						FreeSoundEntity( SoundEnt *ent );
		
	SoundEnt					*PlaySound( std::string name, float volume = 1.0f, bool looping = false, vec3 origin = vec3(0,0,0) );

	float						listenerVolume;
private:
	double						time;

	std::vector<CSound*>		v_Sounds;
	std::vector<SoundEnt*>		v_SndEnts;
};


#if BUILD_TARGET == BUILD_ENGINE
	extern class CSoundSystem *SoundSystem;
#endif

#endif /*_CSoundSystem_*/




/*
#internal_name,file_name,max_volume,min_volume,max_radius,min_radius,looping,channel,

hello_world,$default,1,1,0,0,2D

main_menu,music/slize-twilight-dawn.wav,1,1,0,0,looping,2D,
radio,music/slize-twilight-dawn.wav,1,0.2,128,512,notlooping,ambient,
fire_01,music/slize-twilight-dawn.wav,1,0.2,128,512,looping,effect,

channels are: 2D, ambient, voice, item, weapon, body, effect, auto (selects channel which is free, but never assign to 2D)

max_radius < min_radius
internal_name - alias used by code
file_name - path and name of sound file insode of sound/ folder

volume:
max_volume - maximum volume (quieter sound)
min_volume - minimum volume (loudest sound)

attenuation:
max_radius - distance at which sound volume attenuate
min_radius - distance where sound is is at min_volume and doesn't attenuate

special settings:
looping - determines if sound should repeat or not ('looping' or 'notlooping')
channel - determines in which channel sound should be played
*/


