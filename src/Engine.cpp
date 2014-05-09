/*
===========================================================================

Unkknow Engine Source Code

Copyright (C) 2014 BraXi.
All rights reserved.

This file is part of the Unkknow Engine Source Code ("Unkknow Engine Source Code").

Contact email: thebraxi@o2.pl
Contact website: http://www.braxi.org

CONFIDENTIAL.

===========================================================================
*/



#include "Engine.h"

#include "Renderer/ogl2/GL2_Renderer.h"
#include "Renderer/ogl3/GL3_Renderer.h"

#include "Common/GLFW/GLFW_Window.h"
#include "Common/GLFW/GLFW_Input.h"
#include "Common/GLFW/GLFW_Timer.h"

#include "CGame/Game.h"

class CEngine	*Engine;

CEngine::CEngine()
{
	p_Renderer = NULL;
	p_Window = NULL;

	memset( &config, 0, sizeof( config ) );
}

CEngine::~CEngine()
{
}

bool CEngine::Initialize( int renderer )
{
	config.renderer = renderer;
	config.lowlib = LOWLIB_NONE;

	switch( config.renderer )
	{
	case RENDERER_NONE:
		p_Renderer = NULL;
		config.lowlib = LOWLIB_NONE;
		break;
	case RENDERER_OPENGL_2:
		p_Renderer = new OGL2_Renderer();
		config.lowlib = LOWLIB_GLFW;
		break;
	case RENDERER_OPENGL_3:
		p_Renderer = new OGL3_Renderer();
		config.lowlib = LOWLIB_GLFW;
		break;
	case RENDERER_OPENGL_ES2:
		p_Renderer = NULL;
		config.lowlib = LOWLIB_GLFW;
		break;
	case RENDERER_DIRECTX:
		p_Renderer = NULL;
		config.lowlib = LOWLIB_NONE;
		break;
	default:
		FATAL_ERROR( "Wrong Renderer selected\n" );
		return false;
		break;
	}

	switch( config.lowlib )
	{
	case LOWLIB_GLFW:
		if( !glfwInit() )
			exit( EXIT_FAILURE );
		p_Window = new CGLFW_Window();
		break;
	case LOWLIB_NONE:
	default:
		p_Window = NULL;
		FATAL_ERROR( "Cannot find a lowlib for specified Renderer\n" );
		return false;
		break;
	}

	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 2 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 0 );

	if( !p_Window || !p_Window->Open( 1280, 720, false, 0 ) )
	{
		FATAL_ERROR( "Failed to open window\n" );
		return false;
	}

    PRINTF( "Using renderer: %s\n", RendererStr[config.renderer].c_str() );

    p_Window->SetTitle( WINDOW_TITLE );
	p_Window->MakeContextCurrent();

	if( !p_Renderer || !p_Renderer->Init() )
	{
		FATAL_ERROR( "Failed to initialize selected Renderer\n" );
		return false;
	}

	switch( config.lowlib )
	{
	case LOWLIB_GLFW:
		p_Input = new GLFW_Input();
		p_Timer = new GLFW_Timer();
		break;
	case LOWLIB_NONE:
	default:
		p_Window = NULL;
		FATAL_ERROR( "Cannot find a lowlib for specified Renderer\n" );
		return false;
		break;
	}

	p_Input->BindToWindow( p_Window );
	p_Input->m_UpdateMousePos = false;
	p_Input->SetSystemCursor( true );

	// sound system
	if( !(p_Sound = new CSoundSystem()) )
		return false;

	if( !p_Sound->Init() )
		return false;

	// ui
	if( !(UI = new bxUserInterface()) )
		return false;
	UI->Init();

	Game = new CGame();
//	Game->StartLevel( 0 );

	UI->OpenMenu( "main" );
	return true;
}

void CEngine::Shutdown()
{
	if( Game )
	{
		delete Game;
	}
	if( p_Input )
	{
		p_Input->Unbind();
		delete p_Input;
	}
	if( UI )
	{
		delete UI;
	}
	if( p_Window )
	{
		p_Window->Close();
		delete p_Window;
	}
	if( p_Sound )
	{
		p_Sound->Shutdown();
		delete p_Sound;
	}
	if( p_Renderer )
	{
		p_Renderer->Shutdown();
		delete p_Renderer;
	}
	exit(1);
}

void CEngine::Frame( double delta )
{
	if( Game )
	{
		Game->Simulate( delta );
	}

	//double x,y;
	//glfwGetCursorPos( (GLFWwindow*)p_Window->GetWndHandle(), &x, &y );
	//p_Input->m_MousePos = vec2(x,y);

	UI->UserInterfaceFrame( delta );

	p_Input->PoolActions();

	p_Sound->SoundFrame( delta, Engine->p_Renderer->m_Camera.origin, Engine->p_Renderer->m_Camera.angles );
	p_Renderer->UpdateScreen();
	p_Window->SwapBuffers();
}
