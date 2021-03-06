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

layout(location = 0) in vec3 vertex_Position;
layout(location = 1) in vec3 vertex_Normal;
layout(location = 2) in vec2 vertex_TexCoord;

out vec2 TexCoord;

uniform mat4	ProjectionMatrix;
uniform mat4	ViewMatrix;
uniform mat4	ModelMatrix;

void main()
{
	TexCoord = vertex_TexCoord;

	mat4 mvp = ProjectionMatrix * ViewMatrix * ModelMatrix;
 	gl_Position = vec4(mvp * vec4(vertex_Position,1.0) );

//	gl_Position.xyz = vertexPosition_modelspace;
//	gl_Position.w = 1.0;
}



	
