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

#include "Game.h"
#include "../Renderer/BXMesh.h"
#include "../Engine.h"

static std::vector<CEntity*>	v_Entities;

CGame *Game;

std::vector<CEntity*> CGame::GetEntityArray()
{
	return v_Entities;
}

void CGame::StartLevel( unsigned int map )
{
	Engine->p_Sound->LoadSound( "farts/fart_1" );
	Engine->p_Sound->LoadSound( "farts/fart_2" );
	Engine->p_Sound->LoadSound( "farts/fart_3" );

	level.map = map;
	switch( level.map )
	{
	case 0:
		SpawnEntity( "terrain", vec3(0,0,0) );

		SpawnEntity( "pipe_6", vec3(5,0,-1) );
		SpawnEntity( "pipe_3", vec3(6,0,0) );
		SpawnEntity( "pipe_6", vec3(5,0,1) );

		p_Exit = SpawnEntity( "exit", vec3(19,0,0) );
		break;
	case 1:
		SpawnEntity( "terrain", vec3(0,0,0) );
		//SpawnEntity( "terrain", vec3(40,0,0) );

		SpawnEntity( "pipe_6", vec3(5,0,-1) );
		SpawnEntity( "pipe_3", vec3(5,0,0) );
		SpawnEntity( "pipe_6", vec3(5,0,1) );

		SpawnEntity( "pipe_1", vec3(10,0,-1) );
		SpawnEntity( "pipe_6", vec3(10,0,0) );
		SpawnEntity( "pipe_5", vec3(10,0,1) );

		SpawnEntity( "pipe_1", vec3(15,0,-1) );
		SpawnEntity( "pipe_6", vec3(16,0,0) );
		SpawnEntity( "pipe_6", vec3(15,0,1) );

		p_Exit = SpawnEntity( "exit", vec3(19,0,0) );
		break;
	case 2:
		SpawnEntity( "terrain", vec3(6,0,0) );

		SpawnEntity( "pipe_1", vec3(5,0,-1) );
		SpawnEntity( "pipe_6", vec3(5,0,0) );
		SpawnEntity( "pipe_5", vec3(5,0,1) );

		SpawnEntity( "pipe_6", vec3(6,0,0) );
		SpawnEntity( "pipe_6", vec3(7,0,0) );
		SpawnEntity( "pipe_6", vec3(8,0,0) );
		SpawnEntity( "pipe_6", vec3(9,0,0) );
		SpawnEntity( "pipe_6", vec3(10,0,0) );
		SpawnEntity( "pipe_6", vec3(11,0,0) );
		SpawnEntity( "pipe_6", vec3(12,0,0) );
		SpawnEntity( "pipe_6", vec3(13,0,0) );
		SpawnEntity( "pipe_6", vec3(14,0,0) );
		SpawnEntity( "pipe_6", vec3(15,0,0) );
		SpawnEntity( "pipe_6", vec3(16,0,0) );
		SpawnEntity( "pipe_6", vec3(17,0,0) );
		SpawnEntity( "pipe_6", vec3(18,0,0) );
		SpawnEntity( "pipe_6", vec3(19,0,0) );
		SpawnEntity( "pipe_6", vec3(20,0,0) );
		SpawnEntity( "pipe_6", vec3(21,0,0) );

		SpawnEntity( "pipe_2", vec3(9,0,-1) );
		SpawnEntity( "pipe_3", vec3(13,0,-1) );
		SpawnEntity( "pipe_4", vec3(17,0,-1) );
		SpawnEntity( "pipe_5", vec3(21,0,-1) );

		SpawnEntity( "pipe_4", vec3(9,0,1) );
		SpawnEntity( "pipe_3", vec3(13,0,1) );
		SpawnEntity( "pipe_2", vec3(17,0,1) );
		SpawnEntity( "pipe_1", vec3(21,0,1) );

		p_Exit = SpawnEntity( "exit", vec3(26,0,0) );
		break;

	default:
		SpawnEntity( "terrain", vec3(6,0,0) );
		SpawnEntity( "pipe_6", vec3(5,0,-1) );
		SpawnEntity( "pipe_6", vec3(5,0,0) );
		SpawnEntity( "pipe_6", vec3(5,0,1) );
		p_Exit = SpawnEntity( "exit", vec3(26,0,0) );
		break;


	}

	p_LocalPlayer = SpawnEntity( "player", vec3(-3,8,0) );

	level.gameState = GS_PLAYING;
}

void CGame::DropGame()
{
	memset( &level, 0, sizeof( level ) );
	level.gameState = GS_DEAD;
	p_LocalPlayer = NULL;

	//for( unsigned int i = 0; i < v_Entities.size(); i++ )
	//{
	//	if( v_Entities[i] != NULL )
	//		delete v_Entities[i];
	//}

	v_Entities.clear();
}

void CGame::FastRestart()
{
	if( level.gameState == GS_DEAD )
		return; //why would anybody try to restart a dead game?

	int map = level.map;
	DropGame();
	StartLevel( map );
}

void CGame::Simulate( double delta )
{
	unsigned int i, j;
	if( level.gameState == GS_DEAD || level.gameState == GS_PAUSED )
		return;

	if( level.gameState == GS_FAILED )
	{
		return;
	}

//	if( level.time+0.05 > level.time+delta )
//		return;

	level.timeDelta = delta;
	level.time += delta;

	vec3 gravity = vec3( 0, -20, 0 );

	CEntity *ent = NULL;
	for( i = 0; i < v_Entities.size(); i++ )
	{
		ent = v_Entities[i];

		if( ent->m_MoveType & MOVETYPE_VELOCITY )
			ent->m_Origin = ent->m_Origin + ent->m_Velocity * vec3(delta);
		if( ent->m_MoveType & MOVETYPE_GRAVITY )
		ent->m_Velocity = ent->m_Velocity + gravity * vec3(delta);

		if( ent->m_MoveType != MOVETYPE_NONE ) // hack, just for farty bear
		{
			for( j = 0; j < ent->v_CollBoxes.size(); j++ )
				ent->v_CollBoxes[j]->m_center = ent->m_Origin;
		}

		if( ent->p_Think != NULL )
			ent->p_Think( ent );

		if( p_LocalPlayer != ent )
		{
			for( j = 0; j < p_LocalPlayer->v_CollBoxes.size(); j ++ )
			{
				for( unsigned int idx = 0; idx < ent->v_CollBoxes.size(); idx ++ )
				{
					if( p_LocalPlayer->v_CollBoxes[j]->Overlaps( ent->v_CollBoxes[idx] ) )
					{
						if( ent == p_Exit )
						{
							level.gameState = GS_PAUSED;
							Engine->UI->OpenMenu( "win" );
						}
						else
						{
							level.gameState = GS_FAILED;
							Engine->UI->OpenMenu( "lost" );
						}
					}
				}
			}
		}
	}

	Engine->p_Renderer->m_Camera.origin = p_LocalPlayer->m_Origin;
	Engine->p_Renderer->m_Camera.angles = vec3(0,90,0);
//	Engine->p_Renderer->m_Camera.origin = vec3(5,3,9) + vec3(p_LocalPlayer->m_Origin.x,0,0);


}

static void Player_Think( CEntity *self )
{
	self->m_Velocity.x = 2;

	if( Engine->p_Input->Pressed( 'W' ) )
	{
		Engine->p_Input->m_KeyStates['W'] = false;
		self->m_Velocity.y = 7.2f;
		Engine->p_Sound->PlaySound( "farts/fart_2", 1.0f, false, self->m_Origin-vec3(0,0.7,0) );
	}


	if( Engine->p_Input->Pressed( 'A' ) )
	{
		self->m_Origin.z -= (5*Game->level.timeDelta);
	}
	if( Engine->p_Input->Pressed( 'D' ) )
	{
		self->m_Origin.z += (5*Game->level.timeDelta);
	}

	if( self->m_Origin.z > 1 )
	{
		self->m_Origin.z = 1;

	}
	else if( self->m_Origin.z < -1 )
	{
		self->m_Origin.z = -1;
	}


	if( self->m_Origin.y > 8 )
		self->m_Origin.y = 8;

	if( self->m_Origin.y <= 0 )
	{
		self->m_Origin.y = 0;
		Game->level.gameState = GS_FAILED;
		self->m_MoveType = MOVETYPE_NONE;
		Engine->UI->OpenMenu( "lost" );
	}

}
static void Player_OnTouch( CEntity *self, CEntity *other )
{
	Game->level.gameState = GS_FAILED;
	self->m_MoveType = MOVETYPE_NONE;
}

CEntity *CGame::SpawnEntity( std::string className, vec3 origin )
{
	CEntity *ent = NULL;

	ent = new CEntity();

	memset( ent, 0, sizeof(CEntity) );
	ent->m_Origin = origin;
	ent->m_Scale = vec3(1);

	if( className.compare( "player" ) == 0 )
	{
		ent->p_Think = Player_Think;
		ent->p_OnTouch = Player_OnTouch;

		ent->v_CollBoxes.push_back( new Box( ent->m_Origin+vec3(0,0.18,0), vec3( 0.18, 0.18, 0.18 ) ) );
		//ent->p_Model = Engine->p_Renderer->FindModel( "bear" );

		ent->m_Scale = vec3(0.3);
		ent->m_Angles = vec3(65,0,90);

		ent->m_MoveType = ( MOVETYPE_VELOCITY | MOVETYPE_GRAVITY );
	}
	else
	{
		ent->p_Think = NULL;
		ent->p_OnTouch = NULL;
	}

	if( className.compare( "pipe_1" ) == 0 )
	{
		ent->m_Scale = vec3(0.8,1,0.8);
		ent->v_CollBoxes.push_back( new Box( ent->m_Origin+vec3(0,0.5,0), vec3( 0.5, 0.5, 0.5 ) ) );
		ent->v_CollBoxes.push_back( new Box( ent->m_Origin+vec3(0,5.5,0), vec3( 0.5, 2.5, 0.5 ) ) );
		ent->p_Model = Engine->p_Renderer->FindModel( "pipe_1" );
	}
	else if( className.compare( "pipe_2" ) == 0 )
	{
		ent->m_Scale = vec3(0.8,1,0.8);
		ent->v_CollBoxes.push_back( new Box( ent->m_Origin+vec3(0,1,0), vec3( 0.5, 1, 0.5 ) ) );
		ent->v_CollBoxes.push_back( new Box( ent->m_Origin+vec3(0,6,0), vec3( 0.5, 2, 0.5 ) )  );
		ent->p_Model = Engine->p_Renderer->FindModel( "pipe_2" );
	}
	else if( className.compare( "pipe_3" ) == 0 )
	{
		ent->m_Scale = vec3(0.8,1,0.8);
		ent->v_CollBoxes.push_back( new Box( ent->m_Origin+vec3(0,1.5,0), vec3( 0.5, 1.5, 0.5 ) ) );
		ent->v_CollBoxes.push_back( new Box( ent->m_Origin+vec3(0,6.5,0), vec3( 0.5, 1.5, 0.5 ) ) );
		ent->p_Model = Engine->p_Renderer->FindModel( "pipe_3" );
	}
	else if( className.compare( "pipe_4" ) == 0 )
	{
		ent->m_Scale = vec3(0.8,1,0.8);
		ent->v_CollBoxes.push_back( new Box( ent->m_Origin+vec3(0,2,0), vec3( 0.5, 2, 0.5 ) ) );
		ent->v_CollBoxes.push_back( new Box( ent->m_Origin+vec3(0,7,0), vec3( 0.5, 1, 0.5 ) ) );
		ent->p_Model = Engine->p_Renderer->FindModel( "pipe_4" );
	}
	else if( className.compare( "pipe_5" ) == 0 )
	{
		ent->m_Scale = vec3(0.8,1,0.8);
		ent->v_CollBoxes.push_back( new Box( ent->m_Origin+vec3(0,2.5,0), vec3( 0.5, 2.5, 0.5 ) ) );
		ent->v_CollBoxes.push_back( new Box( ent->m_Origin+vec3(0,7.5,0), vec3( 0.5, 0.5, 0.5 ) ) );
		ent->p_Model = Engine->p_Renderer->FindModel( "pipe_5" );
	}
	else if( className.compare( "pipe_6" ) == 0 )
	{
		ent->m_Scale = vec3(0.8,1,0.8);
		ent->v_CollBoxes.push_back( new Box( ent->m_Origin+vec3(0,4,0), vec3( 0.5, 4, 0.5 ) ) );
		ent->p_Model = Engine->p_Renderer->FindModel( "pipe_6" );
	}

	else if( className.compare( "terrain" ) == 0 )
	{
		ent->m_Scale = vec3(1,1,1.5);
		ent->p_Model = Engine->p_Renderer->FindModel( "terrain" );
	}
	else if( className.compare( "exit" ) == 0 )
	{
		ent->m_Scale = vec3(0.8,1,0.8);
		ent->v_CollBoxes.push_back( new Box( ent->m_Origin+vec3(0.5,4,0), vec3( 0.5, 4, 0.5 ) ) );
		ent->p_Model = Engine->p_Renderer->FindModel( "finish" );
	}

	v_Entities.push_back( ent );
	return ent;
}
