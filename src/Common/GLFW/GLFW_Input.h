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

#ifndef _GLFW_INPUT_H_
#define _GLFW_INPUT_H_

#include "../../Shared.h"

#include "../Input.h"


class GLFW_Input : public CInput
{
public:
	GLFW_Input();
	virtual ~GLFW_Input();

	// Listen for input in this window
	virtual bool			BindToWindow( class CWindow *wnd );
	virtual void			Unbind();

// ===== MOUSE INPUT =====
	// Show or hide system cursor
	virtual void			SetSystemCursor( bool show );

	// Get X&Y position of mouse
	virtual vec2			GetMousePos();

	// Set position of mouse cursor
	virtual void			SetMousePos( double x, double y );

	// Is mouse button pressed?
	virtual bool			MouseButtonPressed( MouseButtons key );

// ===== KEYBOARD INPUT =====
	// Is key pressed?
	virtual bool			Pressed( int key );

	struct GLFWwindow		*p_WndHandle;
private:
};


#endif
