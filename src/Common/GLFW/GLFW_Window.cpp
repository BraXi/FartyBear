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


#include "GLFW_Window.h"


CGLFW_Window::CGLFW_Window()
{
	p_Wnd = NULL;
}

CGLFW_Window::~CGLFW_Window()
{
	Close();
}

bool CGLFW_Window::Open( int width, int height, bool fullScreen, int monitor )
{
	if( WindowHandleIsVaild() )
		Close();

	p_Wnd = glfwCreateWindow( width, height, "", fullScreen ? glfwGetPrimaryMonitor() : NULL, NULL );
	return WindowHandleIsVaild();
}

void CGLFW_Window::Close()
{
	if( !WindowHandleIsVaild() )
		return;
	glfwMakeContextCurrent( NULL );
	glfwSetWindowShouldClose( p_Wnd, 1);
//	glfwDestroyWindow( p_Wnd );
}

void CGLFW_Window::SetTitle( const std::string &title )
{
	if( !WindowHandleIsVaild() )
		return;
	glfwSetWindowTitle( p_Wnd, title.c_str() );
}

bool CGLFW_Window::IsOpen()
{
	return ( (WindowHandleIsVaild() && !glfwWindowShouldClose(p_Wnd) ) ? true : false );
}


vec2 CGLFW_Window::GetSize()
{
	static int p[2];
	vec2 pos;
	pos.x = pos.y = 0.0f;

	if( !WindowHandleIsVaild() )
		return pos;
	
	glfwGetFramebufferSize( p_Wnd, &p[0], &p[1] );

	pos.x = (float)p[0]; 
	pos.y = (float)p[1];
	return pos;
}



vec2 CGLFW_Window::GetPos()
{
	static int p[2];
	vec2 pos;
	pos.x = pos.y = 0.0f;

	if( !WindowHandleIsVaild() )
		return pos;
	
	glfwGetWindowPos( p_Wnd, &p[0], &p[1] );

	pos.x = (float)p[0]; 
	pos.y = (float)p[1];
	return pos;
}

void CGLFW_Window::SetPos( int x, int y )
{
	if( !WindowHandleIsVaild() )
		return;

	glfwSetWindowPos( p_Wnd, x, y );
}

void CGLFW_Window::Iconify()
{
	if( !WindowHandleIsVaild() )
		return;

	glfwIconifyWindow( p_Wnd );
}

void CGLFW_Window::Restore()
{
	if( !WindowHandleIsVaild() )
		return;

	glfwRestoreWindow( p_Wnd );
}

int CGLFW_Window::GetMonitor()
{
	if( !WindowHandleIsVaild() )
		return 0;

	return 0;
}


void CGLFW_Window::MakeContextCurrent()
{
	if( !WindowHandleIsVaild() )
		return;
	glfwMakeContextCurrent( p_Wnd );
}

bool CGLFW_Window::IsContextCurrent()
{
	if( !WindowHandleIsVaild() )
		return false;

	if( glfwGetCurrentContext() == p_Wnd )
		return true;
	return false;
}

void CGLFW_Window::SwapBuffers()
{
	if( !WindowHandleIsVaild() )
		return;

	glfwSwapBuffers( p_Wnd );
	glfwPollEvents();
}

void CGLFW_Window::SwapInterval( bool enabled ) 
{
	if( !WindowHandleIsVaild() )
		return;

	glfwSwapInterval( (int)enabled );
}


bool CGLFW_Window::WindowHandleIsVaild()
{
	return ( p_Wnd ? true : false );
}


void *CGLFW_Window::GetWndHandle()
{
	return p_Wnd;
}