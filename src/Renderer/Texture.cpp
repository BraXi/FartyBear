/*
===========================================================================

Unkknow Engine Source Code

Copyright (C) 2014 BraXi.
All rights reserved.

This file is part of the Unkknow Engine Source Code ("Unkknow Engine Source Code").  

Contact email: thebraxi@o2.pl
Contact website: http://www.braxi.org

CONFIDENTIAL.

===========================================================================
*/


#include "Texture.h"
#include "../Engine.h"

CTexture::CTexture()
{
	m_Name = "";	m_Size[0] = m_Size[1] = 0;
	textureID = 0;
}

CTexture::~CTexture()
{
	m_Name.clear();	m_Size[0] = m_Size[1] = 0;
	Free();
}


bool CTexture::LoadRAW( const std::string &name, unsigned int w, unsigned int h, bool alpha )
{	unsigned char *data = NULL;	FILE *file = NULL;	std::string fileName( GAME_DIR + "images/" + name + ".raw" );	file = fopen( fileName.c_str(), "rb" );
	if( file == NULL )
	{
		PRINTF( "%s not found\n", fileName.c_str() );
		return false;
	}	m_Name = name;	m_Size[0] = w; m_Size[1] = h;

	size_t dataSize = ( m_Size[0] * m_Size[1] * (alpha ? 4 : 3) );
	data = new unsigned char[ dataSize ];
	fread( data, dataSize, 1, file );
	fclose( file );

/*	int bpp = 24;
	//if( h >= 2 )
	{
		if( alpha )
			bpp = 32;

		int rowsToSwap = 0;

		if(h % 2 == 1 )
			rowsToSwap = (h - 1) / 2;
		else
			rowsToSwap = h / 2;

		unsigned char * tempRow = new unsigned char[w*bpp/8];
		if( !tempRow )
		{
			PRINTF( "Unable to flip image" );
			return false;
		}

		//loop through rows to swap
		for(int i = 0; i < rowsToSwap; ++i)
		{
			memcpy( tempRow, &data[i*w*bpp/8], w*bpp/8 );
			memcpy( &data[i*w*bpp/8], &data[(h-i-1)*w*bpp/8], w*bpp/8 );
			memcpy( &data[(h-i-1)*w*bpp/8], tempRow, w*bpp/8 );
		}
		if( tempRow )
			delete [] tempRow;
		tempRow = NULL;
	}*/

	if( Engine && Engine->p_Renderer )
		textureID = Engine->p_Renderer->UploadImage( fileName, data, m_Size[0], m_Size[1], alpha );

	PRINTF( "Loaded: %s\n", fileName.c_str() );

	delete [] data;
	return true;
}


void CTexture::Free()
{
	if( !Engine || !Engine->p_Renderer || textureID == 0 )
		return;
	Engine->p_Renderer->FreeImage( textureID );
}



std::string CTexture::GetName()
{
	return m_Name;
}

unsigned int CTexture::GetWidth()
{
	return m_Size[0];
}

unsigned int CTexture::GetHeight()
{
	return m_Size[1];
}

void CTexture::Bind( unsigned int target )
{
	if( !Engine || !Engine->p_Renderer )
		return;
	Engine->p_Renderer->BindImage( this->textureID );
}

void CTexture::Unbind()
{
	if( !Engine || !Engine->p_Renderer )
		return;		
	Engine->p_Renderer->BindImage( 0 );
}
