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

#ifndef _INPUT_H_
#define _INPUT_H_

#include "../Shared.h"


const int NUM_KEYS = 256;

typedef enum
{
	MB_LEFT,
	MB_MIDDLE,
	MB_RIGHT,
	MB_FUNC4,
	MB_FUNC5,
	NUM_MOUSE_BUTTONS
} MouseButtons;

class CInput
{
public:
	CInput() { m_UpdateMousePos = false; memset(&m_KeyStates, 0, sizeof(m_KeyStates)); }
	virtual ~CInput() { memset(&m_KeyStates, 0, sizeof(m_KeyStates)); }

	// Listen for input in this window
	virtual bool			BindToWindow( class CWindow *wnd ) = 0;
	virtual void			Unbind() = 0;

// ===== MOUSE INPUT =====
	// Show or hide system cursor
	virtual void			SetSystemCursor( bool show ) = 0;

	// Get X&Y position of mouse
	virtual vec2			GetMousePos() = 0;

	// Set position of mouse cursor
	virtual void			SetMousePos( double x, double y ) = 0;

	// Is mouse button pressed?
	virtual bool			MouseButtonPressed( MouseButtons key ) = 0;

	// Mark all keys as not pressed
	void					PoolActions()
	{
		static int i;
		/*for( i = 0; i < NUM_KEYS; i++ )
			m_KeyStates[i] = false;*/
		for( i = 0; i < NUM_MOUSE_BUTTONS; i++ )
			m_MouseButtons[i] = false;
	}

// ===== KEYBOARD INPUT =====
	// Is key pressed?
	virtual bool			Pressed( int key ) = 0;


public:	

	bool				m_UpdateMousePos;
	bool				m_KeyStates[ NUM_KEYS ];
	bool				m_MouseButtons[ NUM_MOUSE_BUTTONS ];
	vec2				m_MousePos;
};


#endif
