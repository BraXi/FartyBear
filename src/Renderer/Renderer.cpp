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

#include "../Engine.h"

#include "Renderer.h"
#include "Texture.h"
#include "Shader.h"
#include "BXMesh.h"

#include "ogl2/GL2_Shader.h"
#include "ogl3/GL3_Shader.h"

static std::vector<CTexture*>	v_Textures;
static std::vector<CShader*>	v_Shaders;
static std::vector<BXMesh*>		v_Models;

CRenderer::CRenderer()
{
	m_Camera.angles = vec3(0);
	m_Camera.origin = vec3(0);
	m_Camera.fov = 60.0f;
	m_Camera.zFar = 32.0f;
	m_Camera.zNear = 0.01f;

	currentTexture = NULL;
}

CRenderer::~CRenderer()
{
//	unsigned int i;

/*	for( i = 0; i < v_Textures.size(); i++ )	delete v_Textures[i];
	for( i = 0; i < v_Shaders.size(); i++ )		delete v_Shaders[i];
	for( i = 0; i < v_Models.size(); i++ )		delete v_Models[i];*/
}


CTexture *CRenderer::FindImage( std::string name )
{
	unsigned int i = 0;
	for( i = 0; i < v_Textures.size(); i++ )
	{
		if( name.compare( v_Textures[i]->GetName() ) == 0 )
			return v_Textures[i];
	}
	return NULL;
}

CTexture *CRenderer::PrecacheImage( std::string name )
{
	CTexture *object = NULL;

	if( (object = FindImage( name )) != NULL )
		return object;
	return NULL;
}

CTexture *CRenderer::PrecacheImage( std::string name, int w, int h, bool alpha )
{
	CTexture *object = NULL;

	if( (object = FindImage( name )) != NULL )
		return object;

	object = new CTexture();
	object->LoadRAW( name, w, h, alpha );

	v_Textures.push_back( object );
	return object;
}

void CRenderer::FreeImage( std::string name )
{
	unsigned int i = 0;
	for( i = 0; i < v_Textures.size(); i++ )
	{
		if( name.compare( v_Textures[i]->GetName() ) == 0 )
		{
			delete v_Textures[i];
			v_Textures.erase( v_Textures.begin() + i );
			break;
		}
	}
}




CShader *CRenderer::FindShader( std::string name )
{
	unsigned int i = 0;
	for( i = 0; i < v_Shaders.size(); i++ )
	{
		if( name.compare( v_Shaders[i]->GetName() ) == 0 )
			return v_Shaders[i];
	}
	return NULL;
}

CShader *CRenderer::PrecacheShader( std::string name )
{
	CShader *object = NULL;

	if( (object = FindShader( name )) != NULL )
		return object;

	switch( Engine->config.renderer )
	{
	case RENDERER_OPENGL_2:
		object = new GL2_Shader();
		object->Load( name );
		break;
	case RENDERER_OPENGL_3:
		object = new GL3_Shader();
		object->Load( name );
		break;
    default:
        FATAL_ERROR( "CRenderer::PrecacheShader() doesn't support renderer: %s\n", RendererStr[Engine->config.renderer].c_str() );
		break;
	}

	v_Shaders.push_back( object );
	return object;
}


void CRenderer::FreeShader( std::string name )
{
	unsigned int i = 0;
	for( i = 0; i < v_Shaders.size(); i++ )
	{
		if( name.compare( v_Shaders[i]->GetName() ) == 0 )
		{
			delete v_Shaders[i];
			v_Shaders.erase( v_Shaders.begin() + i );
			break;
		}
	}
}






BXMesh *CRenderer::FindModel( std::string name )
{
	unsigned int i = 0;
	for( i = 0; i < v_Models.size(); i++ )
	{
		if( name.compare( v_Models[i]->GetName() ) == 0 )
			return v_Models[i];
	}
	return NULL;
}

BXMesh *CRenderer::PrecacheModel( std::string name )
{
	BXMesh *object = NULL;

	if( (object = FindModel( name )) != NULL )
		return object;

	object = new BXMesh();
	object->Load( name );

	v_Models.push_back( object );
	return object;
}


void CRenderer::FreeModel( std::string name )
{
	unsigned int i = 0;
	for( i = 0; i < v_Models.size(); i++ )
	{
		if( name.compare( v_Models[i]->GetName() ) == 0 )
		{
			delete v_Models[i];
			v_Models.erase( v_Models.begin() + i );
			break;
		}
	}
}
