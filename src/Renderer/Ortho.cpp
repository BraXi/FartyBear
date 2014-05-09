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

#include "Renderer.h"
#include "Texture.h"
#include "ogl2/VertexBufferObject.h"
#include "../Engine.h"
#include "Texture.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

static const vec2 VIRTUAL_SCREEN_SIZE = vec2( 640, 480 );

std::vector<CTexture*>	v_fontList;
unsigned int			fontDisplayList;

static const vertex_t Primitive_Quad[4] =
{
	/* pos, normal, uv */
	{vec3( 0, 0, 0 ), vec3( 1, 0, 0 ), vec2( 0,0 )},
	{vec3( 1, 0, 0 ), vec3( 0, 0, 0 ), vec2( 1,0 )},
	{vec3( 1, 1, 0 ), vec3( 0, 0, 0 ), vec2( 1,1 )},
	{vec3( 0, 1, 0 ), vec3( 0, 0, 0 ), vec2( 0,1 )}
};

static VertexBufferObject	*vbo_Quad;



COrtho::COrtho()
{
}

COrtho::~COrtho()
{
	if( vbo_Quad )	delete vbo_Quad;
}

bool COrtho::Init()
{
	vbo_Quad = new VertexBufferObject( VBO_QUADS, (vertex_t*)&Primitive_Quad, 4 );

	v_fontList.push_back( Engine->p_Renderer->PrecacheImage( "fonts/menu", 512,512,false ) );
	return true;
}


void COrtho::AdjustToVirtualScreenSize( float *x, float *y )
{
    float    xscale;
    float    yscale;

	xscale = Engine->p_Window->GetSize().x / VIRTUAL_SCREEN_SIZE.x;
    yscale = Engine->p_Window->GetSize().y / VIRTUAL_SCREEN_SIZE.y;

    if( x ) *x *= xscale;
    if( y ) *y *= yscale;
}


void COrtho::AdjustToVirtualScreenSize( float *x, float *y, float *w, float *h )
{
	AdjustToVirtualScreenSize( x, y );
	AdjustToVirtualScreenSize( w, h );
}


void COrtho::OrthoProjection()
{
    glLoadIdentity();

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	glOrtho( 0.0f, Engine->p_Window->GetSize().x,  Engine->p_Window->GetSize().y, 0.0f, -1.0f, 256.0f );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	Engine->p_Renderer->SetBlending( BLEND_ONE, BLEND_ONE_MINUS_SRC_ALPHA );

}


void COrtho::DrawQuad( vec4 rect, const vec4 c )
{
	AdjustToVirtualScreenSize( &rect.x, &rect.y, &rect.z, &rect.w );

    glPushMatrix();

    glTranslatef( rect.x, rect.y, 0.0f );
    glScalef( rect.z, rect.w, 1.0f );

    glColor4f( c.x, c.y, c.z, c.w );

    vbo_Quad->Render();

    glPopMatrix();
}

void COrtho::DrawString( std::string string, float x, float y, float fontSize, unsigned int font, vec2 align )
{
	y /= 2;

	static int gridSize = 16;
	unsigned int len = string.length();

	fontSize = fontSize * 50.0f;
	float characterWidth = 0.3f * fontSize;
	float characterHeight = 0.225f * fontSize;

	AdjustToVirtualScreenSize( &x, &y );
	AdjustToVirtualScreenSize( &characterWidth, &characterHeight );

    float nx = ( len * characterWidth/3 );
//    float ny = ( len * characterHeight/3 );

	//x = x-nx/2;
	switch( (int)align.x )
	{
	case 2: x -= nx; break;
	case 1: x -= (int)(nx/2); break;
	case 0:
	default:
		break;
	}

	/*switch( (int)align.y )
	{
	case 2: y -= ny; break;
	case 1: y -= (int)(ny/2); break;
	case 0:
	default:
		break;
	}*/

	//DrawString( std::string string, int textureObject, int gridSize, float x, float y, float characterWidth, float characterHeight)
	glPushAttrib( GL_TEXTURE_BIT | GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT );
	glEnable( GL_CULL_FACE );
	glEnable( GL_TEXTURE_2D );

	v_fontList[font]->Bind();
	//glBindTexture( GL_TEXTURE_2D, font );

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glDisable( GL_CULL_FACE );
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);

	glPushMatrix();
	glTranslatef( x, y-characterHeight/1.5, 0.0f );

	glBegin( GL_QUADS );


	for( unsigned int i = 0; i < string.length(); i++ )
	{
		int asciiCode = (int)string[i];

		float cellSize = 1.0f / gridSize;
		float cellX = ((int) asciiCode % gridSize) * cellSize;
		float cellY = ((int) asciiCode / gridSize) * cellSize;

		glTexCoord2f(cellX, cellY);
		glVertex2f(i * characterWidth / 3, y);

		glTexCoord2f(cellX + cellSize, cellY);
		glVertex2f(i * characterWidth / 3 + characterWidth / 2, y);

		glTexCoord2f(cellX + cellSize, cellY + cellSize);
		glVertex2f(i * characterWidth / 3 + characterWidth / 2, y + characterHeight);

		glTexCoord2f(cellX, cellY + cellSize);
		glVertex2f(i * characterWidth / 3, y + characterHeight);
	}
	glEnd();

	glPopMatrix();
	glPopAttrib();
}

#if 0
void COrtho::DrawString( std::string string, float x, float y, float fontSize, unsigned int fontId, vec2 align )
{
	if( fontId >= v_fontList.size() || fontId <= -1 )
		return;

	const int set = 0;

	float	len, nx;


	AdjustToVirtualScreenSize( &x, &y );

	len = (float)string.size();
    nx = (len * (8.0f*fontSize));

	switch( (int)align.x )
	{
	case 2:
		x -= nx;
		break;
	case 1:
		x -= (int)(nx/2);
		break;
	case 0:
	default:
		break;
	}


	v_fontList[fontId]->Bind();

	glPushMatrix();
	{
		glTranslatef( x, y, 0.0f );
		glRotatef( 180, 1, 0, 0 );
		glScalef( fontSize, fontSize, 1 );
		glListBase( fontDisplayList-32+(128*set) );
		glCallLists( (GLsizei)len, GL_UNSIGNED_BYTE, string.c_str() );
	}
	glPopMatrix();

	glScalef( 1,1,1 );
}
#endif
/**
COrtho::DrawString( std::string string, float x, float y, float fontSize, unsigned int fontId, vec2 align )


DrawString( std::string string, int textureObject, int gridSize, float x, float y, float characterWidth, float characterHeight)
renderString(renderString.toString(), fontTexture, 16, -0.9f, 0, 0.3f, 0.225f);
*/
