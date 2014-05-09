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

#ifndef _MENUDEF_
#define _MENUDEF_

#include "ItemDef.h"
#include <vector>

class MenuDef
{
public:
//	MenuDef();
	MenuDef( char *name );
	virtual ~MenuDef();

	// Get name of this menu
	std::string				GetName();

	// Is this menu focused?
	bool					IsActive();

	// Is this menu opened?
	bool					IsOpen();


	// Set default values
	void					SetDefaults();


	std::vector<ItemDef*>	GetGroup( std::string name );

	// Search for ItemDef by name
	ItemDef					*FindItem( std::string name );

	// Add ItemDef to menu
	virtual void			PushItem( ItemDef *newItem );


public:
	bool					drawCursor;


    bool					active;
    bool					opened;
	std::vector<ItemDef*>	itemList;
	std::string				name;

	void					(*Init)( MenuDef *self );			// In here we add items
	void					(*Update)( MenuDef *self );			// In here we update special itemdefs
	void					(*OnOpen)( MenuDef *self );			// When menu opens
	void					(*OnClose)( MenuDef *self );		// ... and when it closes

private: /* Nobody should mess with these outside of MenuDef */

};

#endif /*_MENUDEF*/