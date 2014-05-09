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

#ifndef _ORTHO_H_
#define _ORTHO_H_

#include "../Shared.h"
#include <vector>
#include "Texture.h"

class COrtho
{
public:
	COrtho();
	virtual ~COrtho();

	bool							Init();

	void							AdjustToVirtualScreenSize( float *x, float *y );
	void							AdjustToVirtualScreenSize( float *x, float *y, float *w, float *h );

	void							OrthoProjection();
	void							DrawQuad( vec4 rect, const vec4 c );

	void							DrawString( std::string string, float x, float y, float fontSize = 1.0f, unsigned int fontId = 0, vec2 align = vec2(0,0) );

private:

};


#endif