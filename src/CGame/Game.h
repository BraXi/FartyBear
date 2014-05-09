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


#ifndef _GAME_H_
#define _GAME_H_

#include "Entity.h"

enum GameState
{
	GS_DEAD,
	GS_PLAYING,
	GS_PAUSED,
	GS_FAILED
};

typedef struct level_s
{
	double			time;
	double			timeDelta;

	unsigned int	gameState;
	unsigned int	map;

} level_t;
class CGame
{
public:
	void					StartLevel( unsigned int level );
	void					DropGame();
	void					FastRestart();

	void					Simulate( double delta );

	class CEntity			*SpawnEntity( std::string className, vec3 origin );
	void					FreeEntity( CEntity* ent );

	class CEntity			*p_LocalPlayer;
	class CEntity			*p_Exit;


	std::vector<CEntity*>	GetEntityArray();

	level_t					level;
};

extern class CGame			*Game;

#endif
