/*
===========================================================================

Unkknow Engine Source Code

Copyright (C) 2014 BraXi.
All rights reserved.

This file is part of the Unkknow Engine Source Code ("Unkknow Engine Source Code").

GNU GPL v2 Licensed.

Contact email: thebraxi@o2.pl
Contact website: http://www.braxi.org

===========================================================================
*/

#ifdef _WIN32
    #pragma comment(lib,"Winmm.lib")

	#pragma comment(lib,"opengl32.lib")
	#pragma comment(lib,"glu32.lib")

	#pragma comment(lib,"glfw3.lib")

	#pragma comment(lib,"glew32s.lib")
	#pragma comment(lib,"glew32.lib")

	#pragma comment(lib,"OpenAL32.lib")
	#pragma comment(lib,"alut.lib")
#endif

#include "Engine.h"
#include "Common/Timer.h"

int main()
{
	Engine = new CEngine();

	if( !Engine->Initialize( RENDERER_OPENGL_2 ) )
		return 1;


	while( Engine->p_Window->IsOpen() /*&& Engine->p_Window->IsContextCurrent()*/ )
	{
		Engine->p_Timer->UpdateTime();
		Engine->Frame( Engine->p_Timer->GetTimePassed() );
	}

	if( Engine )
		Engine->Shutdown();

	system( "pause" );
	return 0;
}
