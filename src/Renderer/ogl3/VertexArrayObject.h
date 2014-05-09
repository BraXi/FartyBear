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

#ifndef _VERTEX_ARRAY_OBJECT_
#define _VERTEX_ARRAY_OBJECT_

#include "../../Shared.h"

#include <vector>


#define INDEX_BUFFER 0
#define POS_VB 1
#define NORMAL_VB 2
#define TEXCOORD_VB 3

enum VAOType
{
	VAO_ERROR,
	VAO_TRIS,
	VAO_QUADS
};

typedef struct vertex_s
{
	vec3	origin;
	vec3    normal;
	vec2	uv;
} vertex_t;


class VertexArrayObject
{
public:
	VertexArrayObject( VAOType Type, vertex_t *verts, int numOfVerts );
	VertexArrayObject( VAOType Type, std::vector<vertex_t> verts );
	~VertexArrayObject();

	void			Render( unsigned int startVert = 0, unsigned int numVertsToDraw = 0 );

private:
//    void            Upload( std::vector<vec3> Positions, std::vector<vec3> Normals, std::vector<vec3> TexCoords );
    void            Upload( vertex_t *verts, unsigned int numOfVerts );

	unsigned int	m_VAO;	// GLuint
    unsigned int    m_Buffers[4]; //GLuint

	unsigned int	m_NumVerts;

	VAOType	        m_Type;
};


#endif /*_VERTEX_BUFFER_OBJECT_*/
