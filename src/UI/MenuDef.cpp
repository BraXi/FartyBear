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


#include "MenuDef.h"

// ========================================================================
// Constructor
// ========================================================================

MenuDef::MenuDef( char *nname )
{
	SetDefaults();
	this->name = nname;
}


// ========================================================================
// Destructor
// ========================================================================

MenuDef::~MenuDef()
{
	unsigned int i;
	for( i = 0; i < itemList.size(); i++ )
	{
		ItemDef *item = itemList[i];
		if( item != NULL )
			delete item;
	}
	itemList.clear();

	memset( this, 0, sizeof( this ) );
	SetDefaults();
}



// ========================================================================
// Helpers
// ========================================================================

void MenuDef::SetDefaults()
{
	this->drawCursor = this->active = this->opened = false;
	
	this->Init = NULL;
	this->Update = NULL;
	this->OnOpen = NULL;
	this->OnClose = NULL;
}

std::string MenuDef::GetName()
{
	return name;
}


bool MenuDef::IsOpen()
{
	return this->opened;
}


bool MenuDef::IsActive()
{
	return this->active;
}




/*
=================
FindItem

Search for ItemDef by name and return pointer to it, NULL if not found
=================
*/
ItemDef	*MenuDef::FindItem( std::string name )
{
	unsigned int	i;

	if( name.size() )
		return NULL;

	for( i = 0; i < itemList.size(); i++ )
	{
		if( name.compare( itemList[i]->name ) == 0 )
			return itemList[i];
	}
	return NULL;
}


std::vector<ItemDef*> MenuDef::GetGroup( std::string groupName )
{
	std::vector<ItemDef*> v_Items;

	for( unsigned int i = 0; i < itemList.size(); i++ )
	{
		if( groupName.compare( itemList[i]->name ) == 0 )
		{
			v_Items.push_back( itemList[i] );
		}
	}
	return v_Items;
}


/*
=================
PushItem

Add new item to menu
=================
*/
void MenuDef::PushItem( ItemDef *newItem )
{
	if( newItem == NULL )
		return;

	////if( newItem->name != NULL && FindItem( newItem->name ) != NULL )
	//	return;

	itemList.push_back( newItem );
}