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

#include "VertexBufferObject.h"

#include <GL/glew.h>

static const unsigned int	Quad_numVerts = 4;

static const vertex_t Primitive_Quad[Quad_numVerts] =
{
	/* pos, normal, uv */
	vec3( 0, 0, 0 ), vec3( 0, 0, 0 ), vec2( 0,0 ),
	vec3( 1, 0, 0 ), vec3( 0, 0, 0 ), vec2( 1,0 ),
	vec3( 1, 1, 0 ), vec3( 0, 0, 0 ), vec2( 1,1 ),
	{vec3( 0, 1, 0 ), vec3( 0, 0, 0 ), vec2( 0,1 )}
};


static const vertex_t Primitive_Quad_Upside_Down[Quad_numVerts] =
{
	/* pos, normal, uv */
	vec3( 0, 0, 0 ), vec3( 0, 0, 0 ), vec2( 0,1 ),
	vec3( 1, 0, 0 ), vec3( 0, 0, 0 ), vec2( 1,1 ),
	vec3( 1, 1, 0 ), vec3( 0, 0, 0 ), vec2( 1,0 ),
	vec3( 0, 1, 0 ), vec3( 0, 0, 0 ), vec2( 0,0 )
};

static const vertex_t Tris_Quad[6] =
{
	vec3( 0, -1, 0 ), vec3( 0, 0, -1 ), vec2( 1, 0 ),
	vec3( 1, -1, 0 ), vec3( 0, 0, -1 ), vec2( 0, 0 ),
	vec3( 1, 0, 0 ), vec3( 0, 0, -1 ), vec2( 0, -1 ),

	vec3( 0, 0, 0 ), vec3( 0, 0, -1 ), vec2( 1, -1 ),
	vec3( 0, -1, 0 ), vec3( 0, 0, -1 ), vec2( 1, 0 ),
	vec3( 1, 0, 0 ), vec3( 0, 0, -1 ), vec2( 0, -1 )
};

/*
void init()
{
	VertexBufferObject *Quad = new VertexBufferObject( VBO_TRIS, (vertex_t*)&Tris_Quad, 6 );
	VertexBufferObject *Quad_Upside = new VertexBufferObject( VBO_QUADS, (vertex_t*)&Primitive_Quad_Upside_Down, Quad_numVerts );
}*/

VertexBufferObject::VertexBufferObject( VBOType Type, vertex_t *verts, int numOfVerts )
{
	type = Type;

	numVerts = numOfVerts;
	size_t size = ( numVerts * sizeof(vertex_t) );

	glGenBuffersARB( 1, &vboId );
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, vboId );
	{
		glBufferDataARB( GL_ARRAY_BUFFER_ARB, size, NULL, GL_STATIC_DRAW_ARB );
		glBufferSubDataARB( GL_ARRAY_BUFFER_ARB, 0, size, &verts[0].origin.x );
	}
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );
}


VertexBufferObject::VertexBufferObject( VBOType Type, std::vector<vertex_t> verts )
{
	type = Type;

	numVerts = verts.size();
	size_t size = ( numVerts * sizeof(vertex_t) );

	glGenBuffersARB( 1, &vboId );
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, vboId );
	{
		glBufferDataARB( GL_ARRAY_BUFFER_ARB, size, NULL, GL_STATIC_DRAW_ARB );
		glBufferSubDataARB( GL_ARRAY_BUFFER_ARB, 0, size, &verts[0].origin.x );
	}

	glVertexPointer( 3, GL_FLOAT, sizeof(vertex_t), BUFFER_OFFSET(0) );
	glNormalPointer( GL_FLOAT, sizeof(vertex_t), BUFFER_OFFSET(12) );
	glTexCoordPointer( 2, GL_FLOAT, sizeof(vertex_t), BUFFER_OFFSET(24) );

	glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );
}

VertexBufferObject::~VertexBufferObject()
{
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );
	glDeleteBuffersARB( 1, &vboId );
}

void VertexBufferObject::SetVBOClientState( bool enable )
{
	if( enable )
	{
		glEnableClientState( GL_VERTEX_ARRAY );
		glEnableClientState( GL_NORMAL_ARRAY );
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	}
	else
	{
		glDisableClientState( GL_VERTEX_ARRAY );
		glDisableClientState( GL_NORMAL_ARRAY );
		glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	}
}


void VertexBufferObject::Render( unsigned int startVert, unsigned int numVertsToDraw )
{
	if( type == VBO_ERROR )
		return;

	SetVBOClientState( true );

    glBindBufferARB( GL_ARRAY_BUFFER_ARB, vboId );

	glVertexPointer( 3, GL_FLOAT, sizeof(vertex_t), BUFFER_OFFSET(0) );
	glNormalPointer( GL_FLOAT, sizeof(vertex_t), BUFFER_OFFSET(12) );
	glTexCoordPointer( 2, GL_FLOAT, sizeof(vertex_t), BUFFER_OFFSET(24) );

	if( type == VBO_TRIS )
	{
		if( !numVertsToDraw )
			glDrawArrays( GL_TRIANGLES, 0, numVerts );
		else
			glDrawArrays( GL_TRIANGLES, startVert, numVertsToDraw );
	}
	else if( type == VBO_QUADS )
	{
		if( !numVertsToDraw )
			glDrawArrays( GL_QUADS, 0, numVerts );
		else
			glDrawArrays( GL_QUADS, startVert, numVertsToDraw );
	}

	//glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );

	SetVBOClientState( false );
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );
}
