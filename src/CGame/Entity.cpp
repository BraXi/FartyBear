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

#include "Entity.h"

CEntity lol;

CEntity::CEntity()
{
	className = "";
}

CEntity::~CEntity()
{
	className.clear();
}


void CEntity::Run( double delta )
{

}
