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

#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "../Shared.h"
#include <vector>
#include "Ortho.h"

static const unsigned int DISABLE_CULL_CHANGE = 2;
static const unsigned int DISABLE_DEPTH_CHANGE = 4;
static const unsigned int DISABLE_ALPHATEST_CHANGE = 8;
static const unsigned int DISABLE_BLEND_CHANGE = 16;

enum /* CRenderer::SetCulling() */
{
	CULL_NONE = 0,
	CULL_FRONT,
	CULL_BACK
};
enum /* CRenderer::SetDepthTest() */
{
	DEPTH_DISABLED = 0,
	DEPTH_LESS,
	DEPTH_EQUAL,
	DEPTH_LESS_EQUAL
};
enum /* CRenderer::SetAlphaTest() */
{
	ALPHATEST_ALWAYS,
	ALPHATEST_NEVER
};

enum /* CRenderer::SetBlending() */
{
	BLEND_DISABLED,
	BLEND_ZERO,
	BLEND_ONE,
	BLEND_SRC_COLOR,
	BLEND_DST_COLOR,
	BLEND_ONE_MINUS_SRC_COLOR,
	BLEND_ONE_MINUS_DST_COLOR,
	BLEND_SRC_ALPHA,
	BLEND_DST_ALPHA,
	BLEND_ONE_MINUS_SRC_ALPHA,
	BLEND_ONE_MINUS_DST_ALPHA
};



struct CameraSettings
{
	vec3	origin, angles;
	float	fov, zNear, zFar;
};


struct RendererConfig
{
	unsigned int flags;

	unsigned int cull;
	unsigned int depth;
	unsigned int alphatest;

	unsigned int blend[2];
	bool blendEnabled;

};

class CRenderer
{
public:
	CRenderer();
	virtual ~CRenderer();

public:
	// Initialize rendering API
	virtual	bool			Init() = 0;

	// only called before quitting
	virtual void			Shutdown() = 0;

	// Render frame
	virtual void			UpdateScreen() = 0;

	// prepare renderer for a new level
	virtual void			BeginLevelLoad() = 0;
		
	// throw errors if something is loaded after this point
	virtual void			EndLevelLoad() = 0;

	// Clear color, depth and set clearcolor
	virtual void			Clear( bool color, bool depth, const vec4 &rgba ) = 0;
//	void					Clear4( bool color, bool depth, float r, float g, float b, float a )  { Clear( color, depth vec4( r, g, b, a ) ); }


	// set current color
	virtual void			SetColor( const vec4 &rgba ) = 0;
//	void				SetColor4( float r, float g, float b, float a ) { SetColor( vec4( r, g, b, a ) ); }

	virtual void			SetCulling( unsigned int value ) = 0;
	virtual void			SetDepthTest( unsigned int value ) = 0;
	virtual void			SetAlphaTest( unsigned int value ) = 0;
	virtual void			SetBlending( unsigned int sfactor, unsigned int dfactor ) = 0;

	// upload data to VRAM
	virtual unsigned int	UploadImage( std::string imageName, byte *data, unsigned int width, unsigned int height, bool alpha ) = 0;
	virtual void			FreeImage( unsigned int index ) = 0;
	virtual void			BindImage( unsigned int index ) = 0;

	virtual void			CalculateModelMatrix( mat4 &ModelMatrix, vec3 origin, vec3 angles, vec3 scale ) = 0;

	class CTexture			*FindImage( std::string name );
	class CTexture			*PrecacheImage( std::string name );
	class CTexture			*PrecacheImage( std::string name, int w, int h, bool alpha = false );
	void					FreeImage( std::string name );

	class CShader			*FindShader( std::string name );
	class CShader			*PrecacheShader( std::string name );
	void					FreeShader( std::string name );

	class BXMesh			*FindModel( std::string name );
	class BXMesh			*PrecacheModel( std::string name );
	void					FreeModel( std::string name );

	CameraSettings			m_Camera;

	COrtho					*p_Ortho;
protected:
	RendererConfig			rconf;

	unsigned int 			currentTexture;
};


#endif
