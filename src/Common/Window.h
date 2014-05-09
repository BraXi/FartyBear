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

#ifndef  _WINDOW_H_
#define _WINDOW_H_

#include "../Shared.h"


class CWindow
{
public:
	CWindow() { m_Width = m_Height = 0; m_FullScreen = false; }
	virtual ~CWindow() {}

public:

	// Open and close window
	virtual	bool			Open( int width, int height, bool fullScreen, int monitor ) = 0;
	virtual void			Close() = 0;
	
	// Set the title string of a window
	virtual void			SetTitle( const std::string &title ) = 0;

	// Returns true of window is opened
	virtual bool			IsOpen() = 0;

	// Returns the size of framebuffer (width & height)
	virtual vec2			GetSize() = 0;

	// Get and set position of a window
	virtual vec2			GetPos() = 0;
	virtual void			SetPos( int x, int y ) = 0;

	// Iconify (minimize) window
	virtual void			Iconify() = 0;

	// Restore (open) window
	virtual void			Restore() = 0;

	// Get the ID of monitor the window is currently on
	virtual int			GetMonitor() = 0;

	// Makes the context of this window current
	virtual void			MakeContextCurrent() = 0;

	// Returns true if context is bound to this window
	virtual bool			IsContextCurrent() = 0;

	// Simple as that
	virtual void			SwapBuffers() = 0;

	// Vertical synchronization
	virtual void			SwapInterval( bool enabled ) = 0;

	virtual void			*GetWndHandle() = 0;

protected:	

	int				m_Width, m_Height;
	bool				m_FullScreen;
};


#endif
