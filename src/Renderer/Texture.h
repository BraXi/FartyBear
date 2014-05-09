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

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "../Shared.h"
#include <vector>

class CTexture
{
public:
	CTexture();
	virtual ~CTexture();

	bool					LoadRAW( const std::string &fileName, unsigned int w, unsigned int h, bool alpha = false );
	void					Free();

	void					Bind( unsigned int target = 0 );
	void					Unbind();

	std::string				GetName();
	unsigned int			GetWidth();
	unsigned int			GetHeight();

private:
	
	std::string				m_Name;
	int						m_Size[2];

	unsigned int			textureID;
};

#endif