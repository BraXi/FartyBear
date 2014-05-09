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

#include "GL3_Shader.h"

#include <GL/glew.h>
#include <GL/gl.h>

#include "../../Shared.h"

static const GLchar *DEFAULT_VERTEX_SHADER = "void main() { gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex; }";
static const GLchar *DEFAULT_FRAGMENT_SHADER = "void main() { gl_FragColor = vec4( 0.2, 0.75, 0.1, 1.0 ); }";

static GL3_Shader *p_CurrentShader = NULL;



GL3_Shader::GL3_Shader()
{


}

bool GL3_Shader::Load( std::string &name )
{
	m_Name = "";
	m_Compiled = false;


	// Compile shaders

	std::string vsName( GAME_DIR + "shaders/ogl3/" + name + ".vs" );
	vertexShader = CompileShader( vsName, GL_VERTEX_SHADER );
	if( !CheckShaderObject( vertexShader ) )
	{
		PRINTF( "Failed to compile vertex shader \"%s\" (see console for details)\n", vsName.c_str() );
		return false;
	}

	std::string fsName( GAME_DIR + "shaders/ogl3/" + name + ".fs" );
	fragmentShader = CompileShader( fsName, GL_FRAGMENT_SHADER );
	if( !CheckShaderObject( fragmentShader ) )
	{
		PRINTF( "Failed to compile fragment shader \"%s\" (see console for details)\n", fsName.c_str() );
		return false;
	}


	// Link program
	programObject = glCreateProgram();

	glAttachShader( programObject, vertexShader );
	glAttachShader( programObject, fragmentShader );

	glLinkProgram( programObject );


	GLint linked;
	glGetProgramiv( programObject, GL_LINK_STATUS, &linked );
	if( linked )
	{
		m_Compiled = true;
		PRINTF( "Compiled shader: %s\n", name.c_str() );
	}
	else
	{
		PRINTF("Failed to compile & link shader: %s\n", name.c_str() );
		return false;
	}

	m_Name = name;

	Bind();
	coreUniforms[PROJECTION_MATRIX_UNIFORM] = FindUniform( "ProjectionMatrix" );
	coreUniforms[VIEW_MATRIX_UNIFORM] = FindUniform( "ViewMatrix" );
	coreUniforms[MODEL_MATRIX_UNIFORM] = FindUniform( "ModelMatrix" );
	Unbind();

	return true;
}


GL3_Shader::~GL3_Shader()
{
	if( p_CurrentShader == this )
		this->Unbind();

	if( vertexShader )		glDeleteShader( vertexShader );
	if( fragmentShader )	glDeleteShader( fragmentShader );
	if( programObject )		glDeleteProgram( programObject );

}


int GL3_Shader::GetCoreUniform( int uniform )
{
    if( uniform >= NUM_CORE_UNIFORMS || uniform < 0 )
        return -1;
    return coreUniforms[uniform];
}



void GL3_Shader::Bind()
{
	if( m_Compiled && p_CurrentShader != this )
	{
		glUseProgram( programObject );
		p_CurrentShader = this;
	}
}

void GL3_Shader::Unbind()
{
	p_CurrentShader = NULL;
	glUseProgram( 0 );
}


int GL3_Shader::FindUniform( std::string uniformName )
{
	if( !m_Compiled || p_CurrentShader != this )
		return -1;

	GLint loc = glGetUniformLocation( programObject, (const GLcharARB*)uniformName.c_str() );
	if( loc == -1 )
		PRINTF( "GLShader::FindUniform(): Can't find uniform variable \"%s\"\n", uniformName.c_str() );

	return loc;
}


void GL3_Shader::SendUniform1i( int uniform, int val )
{
	glUniform1i( uniform, val );
}

void GL3_Shader::SendUniform1f( int uniform, float val )
{
	glUniform1f( uniform, val );
}

void GL3_Shader::SendUniform2i( int uniform, int val1, int val2 )
{
	glUniform2i( uniform, val1, val2 );
}

void GL3_Shader::SendUniform2f( int uniform, vec2 val )
{
	glUniform2f( uniform, val.x, val.y );
}

void GL3_Shader::SendUniform3i( int uniform, int val1, int val2, int val3 )
{
	glUniform3i( uniform, val1, val2, val3 );
}

void GL3_Shader::SendUniform3f( int uniform, vec3 val )
{
	glUniform3f( uniform, val.x, val.y, val.z );
}

void GL3_Shader::SendUniform4i( int uniform, int val1, int val2, int val3, int val4 )
{
	glUniform4i( uniform, val1, val2, val3, val4 );
}

void GL3_Shader::SendUniform4f( int uniform, vec4 val )
{
	glUniform4f( uniform, val.x, val.y, val.z, val.w );
}

void GL3_Shader::SendMatrix4( int uniform, mat4 matrix )
{
	glUniformMatrix4fv( uniform, 1, GL_FALSE, glm::value_ptr( matrix ) );
}

void GL3_Shader::SendMatrix3( int uniform, mat3 matrix )
{
	glUniformMatrix3fv( uniform, 1, GL_FALSE, glm::value_ptr( matrix ) );
}






static int GetFileLength( FILE *f )
{
	if( !f )
		return 0;

	fseek( f, 0, SEEK_END );
	int length = ftell( f );
	fseek( f, 0, SEEK_SET );

	return length;
}


unsigned int GL3_Shader::CompileShader( std::string &fileName, unsigned int shaderType )
{
	FILE	*f;
	int		length;
	char	*source;
	unsigned int shader = 0;

	// Open file
	if( !(f = fopen( fileName.c_str(), "rb" )) )
	{
		PRINTF( "GLShader::CompileShader(): \"%s\" not found\n", fileName.c_str() );
		return 0;
	}

	// Read shader
	if( !(length = GetFileLength( f )) )
	{
		PRINTF( "GLShader::CompileShader(): \"%s\" is empty\n", fileName.c_str() );
		return 0;
	}
	source = new char[ length+1 ];
	fread( source, sizeof(char), length, f );
	source[length] = (char)NULL;

	fclose( f );

	// Compile shader
	shader = glCreateShader( shaderType );
	glShaderSource( shader, 1, (const GLcharARB**)&source, (const GLint*)&length );
	glCompileShader( shader );

	delete []source;

	return shader;
}


bool GL3_Shader::CheckShaderObject( unsigned int ShaderObject )
{
	GLint compiled = 0;
	glGetObjectParameterivARB( (GLuint)ShaderObject, GL_COMPILE_STATUS, &compiled );

	if( !compiled )
	{
		GLint blen = 0;
		GLsizei slen = 0;

		glGetShaderiv( (GLuint)ShaderObject, GL_INFO_LOG_LENGTH , &blen );
		if( blen > 1 )
		{
			GLchar* compiler_log = (GLchar*)malloc( blen );

			glGetInfoLogARB( (GLuint)ShaderObject, blen, &slen, compiler_log );
			PRINTF( "Shader compiler log: %s\n", compiler_log );
			free( compiler_log );
		}
		return false;
	}
	return true;
}
