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

#include "GL3_Renderer.h"

#include "../../Engine.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../BXMesh.h"

#include "../Shader.h"
#include "../../CGame/Game.h"

static const GLenum enum_cull[] ={ GL_NONE, GL_FRONT, GL_BACK };
static const GLenum enum_depth[] = { 0, GL_LESS, GL_EQUAL, GL_LEQUAL };
static const GLenum enum_alphatest[] = { GL_ALWAYS, GL_NEVER };
static const GLenum enum_blend[] = { 0, GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_DST_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA };

static mat4 ProjectionMatrix, ViewMatrix, ModelMatrix;

static CShader *p_MainShader, *p_MenuBgShader;

OGL3_Renderer::OGL3_Renderer()
{
	memset( &rconf, 1, sizeof( rconf ) );
}

OGL3_Renderer::~OGL3_Renderer()
{
}

bool OGL3_Renderer::Init()
{
	if( glewInit() != GLEW_OK  )
	{
		PRINTF( "Failed to initialize GLEW\n" );
		return false;
	}

	glEnable( GL_CULL_FACE );
	glEnable( GL_ALPHA_TEST );
	glEnable( GL_TEXTURE_2D );

	memset( &rconf, 1, sizeof( rconf ) );

	currentTexture = 123123;

	rconf.flags = 0;
	rconf.blendEnabled = true; // just to turn it off

	SetCulling( 0 );
	SetCulling( CULL_FRONT );
	SetDepthTest( DEPTH_DISABLED );
	SetDepthTest( DEPTH_LESS_EQUAL );
	SetAlphaTest( 0 );
	SetAlphaTest( 1 );
	SetAlphaTest( 0 );
	SetBlending( 0, 0 );
	SetBlending( BLEND_ONE, BLEND_ONE );
	SetBlending( 0, 0 );
//	glEnable( GL_DEPTH_TEST );
//	glDepthFunc( GL_LEQUAL );

	p_MainShader = PrecacheShader( "main" );
	p_MenuBgShader = PrecacheShader( "menubg" );

	PrecacheImage( "bear", 1024, 512, false );
	PrecacheImage( "pipe", 256, 128, false );
	PrecacheImage( "grass", 1024, 512, false );
	PrecacheImage( "dirt", 512, 512, false );
	PrecacheImage( "finish", 512, 256, false );

	PrecacheModel( "pipe_1" );
	PrecacheModel( "pipe_2" );
	PrecacheModel( "pipe_3" );
	PrecacheModel( "pipe_4" );
	PrecacheModel( "pipe_5" );
	PrecacheModel( "pipe_6" );
	PrecacheModel( "finish" );
	PrecacheModel( "bear" );
	PrecacheModel( "terrain" );

	p_Ortho->Init();

	return true;
}

void OGL3_Renderer::Shutdown()
{
	glUseProgram( 0 );
	glBindTexture( GL_TEXTURE_2D, 0 );
}


void OGL3_Renderer::DrawWorld()
{
	if( !Game || Game->level.gameState == GS_DEAD )
		return;

	CEntity *ent;
	for( unsigned int i = 0; i < Game->GetEntityArray().size(); i++ )
	{
		ent = Game->GetEntityArray()[i];
		if( ent->p_Model == NULL )
			continue;

		CalculateModelMatrix( ModelMatrix, ent->m_Origin, ent->m_Angles, ent->m_Scale );
		p_MainShader->SendMatrix4( p_MainShader->GetCoreUniform(2), ModelMatrix );
		ent->p_Model->Render();
	}
}
void OGL3_Renderer::UpdateScreen()
{
	glViewport( 0, 0, (GLsizei)Engine->p_Window->GetSize().x, (GLsizei)Engine->p_Window->GetSize().y );
	Clear( true, true, vec4(0,0.74,0.52,1) );

	//m_Camera.angles = vec3(2,0,0);
	CalculateProjectionMatrix( m_Camera.origin, m_Camera.angles, m_Camera.fov, m_Camera.zNear, m_Camera.zFar );

	Engine->p_Renderer->SetBlending( BLEND_DISABLED, BLEND_DISABLED );
	Engine->p_Renderer->SetCulling( CULL_FRONT );

	p_MainShader->Bind();

    DrawWorld();

	p_MainShader->Unbind();
}

void OGL3_Renderer::BeginLevelLoad()
{
}

void OGL3_Renderer::EndLevelLoad()
{
}

void OGL3_Renderer::Clear( bool color, bool depth, const vec4 &clearColor )
{
	GLbitfield clear = 0;
	if( color || depth )
	{
		if( color )	clear |= GL_COLOR_BUFFER_BIT;
		if( depth )	clear |= GL_DEPTH_BUFFER_BIT;
		glClear( clear );
	}
	glClearColor( clearColor.x, clearColor.y, clearColor.w, clearColor.z );
}

void OGL3_Renderer::SetColor( const vec4 &c )
{
	glColor4f( c.x, c.y, c.z, c.w );
}

void OGL3_Renderer::SetCulling( unsigned int value )
{
	if( (rconf.flags & DISABLE_CULL_CHANGE) || value > CULL_BACK || value < CULL_NONE || value == rconf.cull )
		return;
	rconf.cull = value;
	glCullFace( enum_cull[rconf.cull] );
}


void OGL3_Renderer::SetDepthTest( unsigned int value )
{
	if( (rconf.flags & DISABLE_DEPTH_CHANGE) || value > DEPTH_LESS_EQUAL || value < DEPTH_DISABLED || rconf.depth == value )
        return;

	if( !rconf.depth && value > 0 )
		glEnable( GL_DEPTH_TEST );

	rconf.depth = value;

	if( !rconf.depth )
	{
        glDisable( GL_DEPTH_TEST );
        return;
	}
	glDepthFunc( enum_depth[rconf.depth] );
}


void OGL3_Renderer::SetAlphaTest( unsigned int value )
{
	if( (rconf.flags & DISABLE_ALPHATEST_CHANGE) || value > ALPHATEST_NEVER || value < ALPHATEST_ALWAYS || value == rconf.alphatest )
		return;
	rconf.alphatest = value;
	glCullFace( enum_alphatest[rconf.alphatest] );
}

void OGL3_Renderer::SetBlending( unsigned int sfactor, unsigned int dfactor )
{
	if( (rconf.flags & DISABLE_BLEND_CHANGE) || !rconf.blendEnabled && sfactor == 0 )
    {
        return;
    }

	if( rconf.blend[0] == sfactor && rconf.blend[1] == dfactor )
		return;

	if( !rconf.blendEnabled && sfactor >= 0 )
	{
		 glEnable( GL_BLEND );
		 rconf.blendEnabled = true;
	}

	if( rconf.blendEnabled && sfactor == 0 )
	{
		 glDisable( GL_BLEND );
		 rconf.blendEnabled = false;
	}


    glBlendFunc( enum_blend[sfactor], enum_blend[dfactor] );

	rconf.blend[0] = sfactor;
    rconf.blend[1] = dfactor;
}

unsigned int OGL3_Renderer::UploadImage( std::string imageName, byte *data, unsigned int width, unsigned int height, bool alpha )
{
	unsigned int textureId;
	glGenTextures( 1, &textureId );
	glBindTexture( GL_TEXTURE_2D, textureId );

	int internalFormat = (alpha ? GL_RGBA : GL_RGB);

	glTexImage2D( GL_TEXTURE_2D, 0, internalFormat, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, reinterpret_cast<void*>(data) );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

#if 0
	// pixelate texture
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
#endif

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	return textureId;
}

void OGL3_Renderer::FreeImage( unsigned int index )
{
	if( CRenderer::currentTexture == index && index != 0 )
		BindImage( 0 );
	glDeleteTextures( 1, &index );
}

void OGL3_Renderer::BindImage( unsigned int index )
{
//	if( CRenderer::currentTexture == index )
//		return;
	CRenderer::currentTexture = index;
	glBindTexture( GL_TEXTURE_2D, index );
}


void OGL3_Renderer::CalculateProjectionMatrix( vec3 projPos, vec3 projRot, float fov, float zNear, float zFar )
{
    ProjectionMatrix = ViewMatrix = mat4(1); //identity
	ProjectionMatrix = glm::perspective( fov, (Engine->p_Window->GetSize().x / Engine->p_Window->GetSize().y), zNear, zFar );

    ViewMatrix = mat4(1);
    ViewMatrix = glm::rotate( ViewMatrix, projRot.x, vec3(1,0,0) );
    ViewMatrix = glm::rotate( ViewMatrix, projRot.y, vec3(0,1,0) );
    ViewMatrix = glm::rotate( ViewMatrix, projRot.z, vec3(0,0,1) );
    ViewMatrix = glm::translate( ViewMatrix, vec3(-projPos.x, -projPos.y, -projPos.z) );
}

void OGL3_Renderer::CalculateModelMatrix( mat4 &ModelMatrix, vec3 origin, vec3 angles, vec3 scale )
{
/*
*   !!! BEWARE !!!
*	These lines actually performs the scaling FIRST and THEN the rotation, and THEN the translation.
*/
    // translation * rotation * scale

	ModelMatrix = glm::translate( mat4(1), origin );

	ModelMatrix = glm::rotate( ModelMatrix, angles.x, vec3(1,0,0) );
	ModelMatrix = glm::rotate( ModelMatrix, angles.y, vec3(0,1,0) );
	ModelMatrix = glm::rotate( ModelMatrix, angles.z, vec3(0,0,1) );

	ModelMatrix = glm::scale( ModelMatrix, scale );

    //glUniformMatrix4fv( 0, 1, GL_FALSE, &ModelMatrix[0][0] );
//	glUniformMatrix4fv( p_CurrentShader->GetCoreUniform(MODEL_MATRIX_UNIFORM), 1, GL_FALSE, glm::value_ptr(ModelMatrix) );
}
