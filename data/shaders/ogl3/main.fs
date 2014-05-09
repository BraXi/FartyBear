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

#version 330 core

in vec2 TexCoord;
out vec4 color;

uniform sampler2D ColorMap;
uniform vec4 Color;

void main( void )
{
	color = texture2D( ColorMap, TexCoord ) * Color;
}

