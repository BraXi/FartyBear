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

#ifndef _ENGINE_H_
#define _ENGINE_H_

#define VERSION "0.4"
#define NAME "Farty Bear By BraXi (Sounds by SliZe)"
#define WINDOW_TITLE ( NAME " " VERSION " (" __DATE__ ")" )

#include "Shared.h"

#include "Renderer/Renderer.h"
#include "Common/Window.h"
#include "Common/Input.h"
#include "Common/Timer.h"

#include "UI/UserInterface.h"
#include "Sound/SoundSystem.h"

enum AviableRenderers
{
	RENDERER_NONE,
	RENDERER_OPENGL_2,
	RENDERER_OPENGL_3,
	RENDERER_OPENGL_ES2,
	RENDERER_DIRECTX
};

const std::string RendererStr[] = { "RENDERER_NONE", "RENDERER_OPENGL_2", "RENDERER_OPENGL_3", "RENDERER_OPENGL_ES2", "RENDERER_DIRECTX" };

enum AviableLowLibs
{
	LOWLIB_NONE,
	LOWLIB_GLFW
};

struct econf
{
	int		renderer;	// AviableRenderers
	int		lowlib;		// AviableLowLibs

	vec2	screensize;
};


class CEngine
{
public:
	CEngine();
	virtual ~CEngine();

public:

	bool					Initialize( int Renderer );
	void					Shutdown();

	void					Frame( double delta );

	class CRenderer			*p_Renderer;
	class CWindow			*p_Window;
	class CInput			*p_Input;
	class CTimer			*p_Timer;
	class CSoundSystem		*p_Sound;

	class bxUserInterface	*UI;


	econf					config;

private:

};

extern class CEngine		*Engine;
#endif
