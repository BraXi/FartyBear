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

#ifndef _GLFW_WINDOW_H_
#define _GLFW_WINDOW_H_

#include "../../Shared.h"

#include "../Window.h"
#include <GLFW/glfw3.h>

class CGLFW_Window : public CWindow
{
public:
	CGLFW_Window();
	virtual ~CGLFW_Window();

public:

	// Open and close window
	bool				Open( int width, int height, bool fullScreen, int monitor );
	virtual void			Close();
	
	// Set the title string of a window
	virtual void			SetTitle( const std::string &title );

	// Returns true of window is opened
	virtual bool			IsOpen();

	// Returns the size of framebuffer (width & height)
	virtual vec2			GetSize();

	// Get and set position of a window
	virtual vec2			GetPos();
	virtual void			SetPos( int x, int y );

	// Iconify (minimize) window
	virtual void			Iconify();

	// Restore (open) window
	virtual void			Restore();

	// Get the ID of monitor the window is currently on
	virtual int			GetMonitor();

	// Makes the context of this window current
	virtual void			MakeContextCurrent();

	// Returns true if context is bound to this window
	virtual bool			IsContextCurrent();

	// Simple as that
	virtual void			SwapBuffers();

	// Vertical synchronization
	virtual void			SwapInterval( bool enabled );

	virtual void			*GetWndHandle();

private:

	bool				WindowHandleIsVaild();
	GLFWwindow			*p_Wnd;
};


#endif
