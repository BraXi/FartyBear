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

#version 110

uniform sampler2D ColorMap;
uniform vec4 Color;

uniform bool UV_Override;
uniform vec2 U;
uniform vec2 V;
void main( void )
{
	gl_FragColor = texture2D( ColorMap, gl_TexCoord[0].xy ) * Color;
}
