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

#ifndef _SHADER_H_
#define _SHADER_H_

#include "../Shared.h"

enum CoreShaderUniforms
{
    PROJECTION_MATRIX_UNIFORM,
    VIEW_MATRIX_UNIFORM,
    MODEL_MATRIX_UNIFORM,
    NUM_CORE_UNIFORMS
};


class CShader
{
public:
	CShader() {}
	virtual ~CShader() {}

	std::string						GetName() { return m_Name; };

	virtual bool					Load( std::string &shadername ) = 0;
	virtual void					Bind() = 0;
	virtual void					Unbind() = 0;

	virtual int						FindUniform( std::string uniformName ) = 0;
    virtual int						GetCoreUniform( int uniform ) = 0; // enum CoreShaderUniforms

	virtual void					SendUniform1i( int uniform, int val ) = 0;
	virtual void					SendUniform1f( int uniform, float val ) = 0;

	virtual void					SendUniform2i( int uniform, int val1, int val2 ) = 0;
	virtual void					SendUniform2f( int uniform, vec2 val ) = 0;

	virtual void					SendUniform3i( int uniform, int val1, int val2, int val3 ) = 0;
	virtual void					SendUniform3f( int uniform, vec3 val ) = 0;

	virtual void					SendUniform4i( int uniform, int val1, int val2, int val3, int val4 ) = 0;
	virtual void					SendUniform4f( int uniform, vec4 val ) = 0;

	virtual void					SendMatrix4( int uniform, mat4 matrix ) = 0;
	virtual void					SendMatrix3( int uniform, mat3 matrix ) = 0;

protected:
	std::string						m_Name;
	bool							m_Compiled;
};

#endif
