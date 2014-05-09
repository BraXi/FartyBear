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

varying vec3	vNormal;

uniform mat4	ProjectionMatrix;
uniform mat4	ViewMatrix;
uniform mat4	ModelMatrix;

void main()
{
	vNormal = gl_NormalMatrix * gl_Normal;

	gl_TexCoord[0] = gl_MultiTexCoord0;

	mat4 mvp = ProjectionMatrix * ViewMatrix * ModelMatrix;
 	gl_Position = vec4(mvp * gl_Vertex);
}



	
