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


#ifndef _GL3SHADER_
#define _GL3SHADER_

#include "../Shader.h"


class GL3_Shader : public CShader
{
public:
	GL3_Shader();
	virtual ~GL3_Shader();

	virtual bool					Load( std::string &name );
	virtual void					Bind();
	virtual void					Unbind();

	virtual int						FindUniform( std::string uniformName );
	virtual int						GetCoreUniform( int uniform ); // enum CoreShaderUniforms


	virtual void					SendUniform1i( int uniform, int val );
	virtual void					SendUniform1f( int uniform, float val );

	virtual void					SendUniform2i( int uniform, int val1, int val2 );
	virtual void					SendUniform2f( int uniform, vec2 val );

	virtual void					SendUniform3i( int uniform, int val1, int val2, int val3 );
	virtual void					SendUniform3f( int uniform, vec3 val );

	virtual void					SendUniform4i( int uniform, int val1, int val2, int val3, int val4 );
	virtual void					SendUniform4f( int uniform, vec4 val );

	virtual void					SendMatrix4( int uniform, mat4 matrix );
	virtual void					SendMatrix3( int uniform, mat3 matrix );

private:
    int								coreUniforms[NUM_CORE_UNIFORMS];

	unsigned int					programObject; /*GLuint*/
	unsigned int					vertexShader, fragmentShader; /*GLuint*/

	bool							CheckShaderObject( unsigned int ShaderObject );
	unsigned int					CompileShader( std::string &fileName, unsigned int shaderType );
};


#endif /*_GLSHADER_*/
