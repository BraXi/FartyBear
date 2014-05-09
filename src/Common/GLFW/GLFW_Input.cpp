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

#include "GLFW_Input.h"
#include "GLFW_Window.h"
#include <GLFW/glfw3.h>
#include <vector>
#include "../../Engine.h"

static void KeyCallback( GLFWwindow* window, int key, int scancode, int action, int mods );
static void CharCallback( GLFWwindow* window, unsigned int key );
static void MouseButtonCallback( GLFWwindow* window, int button, int action, int mods );
static void MousePositionCallback( GLFWwindow* window, double x, double y );

static std::vector<GLFW_Input*> v_Input;

GLFW_Input *GetInputforWndPtr( GLFWwindow *ptr )
{
	for( unsigned int i = 0; i < v_Input.size(); i++ )
	{
		if( v_Input[i]->p_WndHandle == ptr )
			return v_Input[i];
	}
	return NULL;
}

GLFW_Input::GLFW_Input()
{
	p_WndHandle = NULL;
	v_Input.push_back( this );
}

GLFW_Input::~GLFW_Input()
{
	for( unsigned int i = 0; i < v_Input.size(); i++ )
	{
		if( v_Input[i] == this )
		{
			v_Input.erase( v_Input.begin()+i );
			break;
		}
	}
}

bool GLFW_Input::BindToWindow( class CWindow *wnd )
{
	if( !wnd )
		return false;

	p_WndHandle = (GLFWwindow*)wnd->GetWndHandle();

	glfwSetKeyCallback( p_WndHandle, KeyCallback );
	glfwSetCharCallback( p_WndHandle, CharCallback );
	glfwSetMouseButtonCallback( p_WndHandle, MouseButtonCallback );
	glfwSetCursorPosCallback( p_WndHandle, MousePositionCallback );
	return true;
}

void GLFW_Input::Unbind()
{
	PoolActions();

	glfwSetKeyCallback( p_WndHandle, NULL );
	glfwSetCharCallback( p_WndHandle, NULL );
	glfwSetMouseButtonCallback( p_WndHandle, NULL );
	glfwSetCursorPosCallback( p_WndHandle, NULL );
}

void GLFW_Input::SetSystemCursor( bool show )
{
	glfwSetInputMode( p_WndHandle, GLFW_CURSOR, (show ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN) );
}

vec2 GLFW_Input::GetMousePos()
{
	return m_MousePos;
}

void GLFW_Input::SetMousePos( double x, double y )
{
	glfwSetCursorPos( p_WndHandle, x, y );
	m_MousePos = vec2( x, y );
}


bool GLFW_Input::MouseButtonPressed( MouseButtons key )
{
	if( (int)key >= NUM_MOUSE_BUTTONS || 0 > (int)key )
		return false;

	if( m_MouseButtons[key] == true )
		return true;

	return false;
}


bool GLFW_Input::Pressed( int key )
{
	if( key > NUM_KEYS || 0 > key )
		return false;

	if( m_KeyStates[key] == true )
		return true;

	return false;
}





static void KeyCallback( GLFWwindow* window, int key, int scancode, int action, int mods )
{
	if( key > NUM_KEYS || 0 > key )
		return;

	bool pressed = action == GLFW_PRESS;

	GLFW_Input *wnd = GetInputforWndPtr( window );
	if( wnd )
		wnd->m_KeyStates[key] = pressed;

}


static void CharCallback( GLFWwindow* window, unsigned int key )
{
	if( key >= NUM_KEYS || 0 > key )
		return;
}


static void MouseButtonCallback( GLFWwindow* window, int button, int action, int mods )
{
	if( button > NUM_MOUSE_BUTTONS || 0 > button )
		return;

	GLFW_Input *wnd = GetInputforWndPtr( window );
	if( wnd )
		wnd->m_MouseButtons[button] = (action == GLFW_PRESS);
}


static void MousePositionCallback( GLFWwindow* window, double x, double y )
{
	GLFW_Input *wnd = GetInputforWndPtr( window );
	if( !wnd || !wnd->m_UpdateMousePos )
		return;

//	wnd->Ge
//	wnd->m_MousePos = vec2(x,y);
	// make sure our mouse doesn't go outside window
/*	if( x < 0 )
		x = 1;
	else if( x > Engine->config.screensize.x )
		x = Engine->config.screensize.x-5;
	if( y < 0 )
		y = 0;
	else if( y > Engine->config.screensize.y )
		y = Engine->config.screensize.y-5;*/

	wnd->SetMousePos( x, y );
}
