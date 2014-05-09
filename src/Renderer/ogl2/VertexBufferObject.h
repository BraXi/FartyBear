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

#ifndef _VERTEX_BUFFER_OBJECT_
#define _VERTEX_BUFFER_OBJECT_

#include "../../Shared.h"

#include <vector>

enum VBOType
{
	VBO_ERROR,
	VBO_TRIS,
	VBO_QUADS
};


typedef struct vertex_s
{
	vec3	origin;
	vec3    normal;
	vec2	uv;
} vertex_t;


class VertexBufferObject
{
public:
	VertexBufferObject( VBOType Type, vertex_t *verts, int numOfVerts );
	VertexBufferObject( VBOType Type, std::vector<vertex_t> verts );
	~VertexBufferObject();

	void			Render( unsigned int startVert = 0, unsigned int numVertsToDraw = 0 );

private:
	unsigned int	vboId;	// GLuint
	unsigned int	numVerts;

	VBOType			type;

	void			SetVBOClientState( bool enable );
};


#endif /*_VERTEX_BUFFER_OBJECT_*/
