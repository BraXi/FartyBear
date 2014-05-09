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

#include "VertexArrayObject.h"

#include <GL/glew.h>


VertexArrayObject::VertexArrayObject( VAOType Type, vertex_t *verts, int numOfVerts )
{
    m_Type = Type;
    m_NumVerts = numOfVerts;

    Upload( verts, numOfVerts );
}

VertexArrayObject::VertexArrayObject( VAOType Type, std::vector<vertex_t> verts )
{
    m_Type = Type;
    m_NumVerts = verts.size();

    Upload( (vertex_t*)&verts, m_NumVerts );
}

VertexArrayObject::~VertexArrayObject()
{
    glDeleteBuffers( 4, m_Buffers );
    glDeleteVertexArrays( 1, &m_VAO );
}

void VertexArrayObject::Render( unsigned int startVert, unsigned int numVertsToDraw )
{
    if( m_Type == VAO_ERROR )
		return;

    GLenum mode = (m_Type == VAO_TRIS) ? GL_TRIANGLES : VAO_QUADS;

    glBindVertexArray( m_VAO );
//    glDrawElementsBaseVertex( GL_TRIANGLES, m_Entries[i].NumIndices, GL_UNSIGNED_INT, (void*)(sizeof(unsigned int) * m_Entries[i].BaseIndex), m_Entries[i].BaseVertex);
    if( !numVertsToDraw )
        glDrawArrays( mode, 0, m_NumVerts );
    else
        glDrawArrays( mode, startVert, numVertsToDraw );
    glBindVertexArray( 0 );
}

void VertexArrayObject::Upload( vertex_t *verts, unsigned int numOfVerts )
{
    std::vector<vec3> Positions;
    std::vector<vec3> Normals;
    std::vector<vec2> TexCoords;

    for( unsigned int i = 0; i < (unsigned int)numOfVerts; i++ )
    {
        Positions.push_back( verts[i].origin );
        Normals.push_back( verts[i].normal );
        TexCoords.push_back( verts[i].uv );
    }

    glGenVertexArrays( 1, &m_VAO );
    glBindVertexArray( m_VAO );

    glGenBuffers( 4, m_Buffers );

    // !!! layout locations must match shaders !!!

    glBindBuffer( GL_ARRAY_BUFFER, m_Buffers[POS_VB] );
    glBufferData( GL_ARRAY_BUFFER, sizeof(Positions[0]) * Positions.size(), &Positions[0], GL_STATIC_DRAW );
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );

    glBindBuffer( GL_ARRAY_BUFFER, m_Buffers[NORMAL_VB] );
    glBufferData( GL_ARRAY_BUFFER, sizeof(Normals[0]) * Normals.size(), &Normals[0], GL_STATIC_DRAW );
    glEnableVertexAttribArray( 1 );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, 0 );

    glBindBuffer( GL_ARRAY_BUFFER, m_Buffers[TEXCOORD_VB] );
    glBufferData( GL_ARRAY_BUFFER, sizeof(TexCoords[0]) * TexCoords.size(), &TexCoords[0], GL_STATIC_DRAW );
    glEnableVertexAttribArray( 2 );
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 0, 0 );



//    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_Buffers[INDEX_BUFFER] );
//    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices[0]) * Indices.size(), &Indices[0], GL_STATIC_DRAW );

    glBindVertexArray( 0 );

    Positions.clear();
    Normals.clear();
    TexCoords.clear();
}
