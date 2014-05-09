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

#ifndef _OGL2_RENDERER_H_
#define _OGL2_RENDERER_H_

#include "../Renderer.h"






class OGL2_Renderer : public CRenderer
{
public:
	OGL2_Renderer();
	virtual ~OGL2_Renderer();

public:
	virtual	bool			Init();
	virtual void			Shutdown();

	virtual void			UpdateScreen();

	virtual void			BeginLevelLoad();
	virtual void			EndLevelLoad();

	virtual void			Clear( bool color, bool depth, const vec4 &rgba );

	virtual void			SetColor( const vec4 &rgba );

	virtual void			SetCulling( unsigned int value );
	virtual void			SetDepthTest( unsigned int value );
	virtual void			SetAlphaTest( unsigned int value );
	virtual void			SetBlending( unsigned int sfactor, unsigned int dfactor );

	// upload data to VRAM
	virtual unsigned int	UploadImage( std::string imageName, byte *data, unsigned int width, unsigned int height, bool alpha );
	virtual void			FreeImage( unsigned int index );
	virtual void			BindImage( unsigned int index );

	virtual void			CalculateModelMatrix( mat4 &ModelMatrix, vec3 origin, vec3 angles, vec3 scale );

private:
	void					DrawWorld();
	void					CalculateProjectionMatrix( vec3 projPos, vec3 projRot, float fov, float zNear, float zFar );

};

#endif