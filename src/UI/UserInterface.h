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

#ifndef _BXUSERINTERFACE_
#define _BXUSERINTERFACE_

#include "../Shared.h"
#include "MenuDef.h"

class bxUserInterface
{
public:
	bxUserInterface();
	~bxUserInterface();

	// Initialize menus
	void					Init();

	// Update User Interface at each frame
	void					UserInterfaceFrame( double time );

	// Draw all menus, 
	void					Draw();


	// Add new menu to an array 
	void					PushMenu( MenuDef *menu );

	// Returns true if menu is opened
	bool					IsMenuOpen( std::string name );

	// Open menu and set focus on it
	void					OpenMenu( std::string name );

	// Close menu and focus previous menu on opened menus list
	void					CloseMenu( std::string name );


	// Return number of currently opened menus
	unsigned int			GetNumOpenedMenus();

	// Return number of all loaded menus
	unsigned int			GetNumMenus();


private:

	// Number of currently opened menus
	int						numOpenedMenus;

	// An array of MenuDefs (menus)
	std::vector<MenuDef*>	menuList;

	virtual void			CleanMemory();

};


#endif /*_BXUSERINTERFACE_*/
