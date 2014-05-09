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

#include "UserInterface.h"

#include "../CGame/Game.h"
#include "../Engine.h"

#include "MenuList.h"


// ========================================================================
// Constructor
// ========================================================================

bxUserInterface::bxUserInterface()
{
	numOpenedMenus = 0;
}


// ========================================================================
// Destructor
// ========================================================================

bxUserInterface::~bxUserInterface()
{
	numOpenedMenus = 0;
	CleanMemory();
}


// ========================================================================
// Create Menus
// ========================================================================

void bxUserInterface::Init()
{
	Engine->p_Sound->LoadSound( "click" );

	Init_Menu_Main();
	Init_Menu_Play();
	Init_Menu_SelectMap();
	Init_Menu_Lost();
	Init_Menu_Win();
	Init_Menu_Exit();
}



/*
=================
IsMenuOpened

Returns true if menu is open
=================
*/
bool bxUserInterface::IsMenuOpen( std::string name )
{
	unsigned int	i;

	for( i = 0; i < GetNumMenus(); i++ )
	{
		if( name.compare( menuList[i]->GetName() ) == 0 && !menuList[i]->IsOpen() )
			return true;
	}
	return false;
}



/*
=================
IsMenuOpened

Returns true if menu is open
=================
*/
void bxUserInterface::OpenMenu( std::string name )
{
	unsigned int	i, j;
	MenuDef			*menu;


	if( !GetNumMenus() )
	{
		PRINTF( "bxUserInterface::OpenMenu(): No MenuDefs\n" );
		return;
	}

	for( i = 0; i < GetNumMenus(); i++ )
	{
		menu = menuList[i];

		if( name.compare( menuList[i]->GetName() ) == 0 && !menuList[i]->IsOpen() )
		{
			numOpenedMenus ++;
			menu->opened = true;
			menu->active = true;

			//Common->Printf( "Opened Menu %s\n", menu->name );
			if( menuList[i]->OnOpen != 0x00000000 )
				menuList[i]->OnOpen( menu );

			// deactivate other menus
			for( j = 0; j < GetNumMenus(); j++ )
			{
				if( menuList[j]->IsActive() && j != i )
					menuList[j]->active = false;
			}
			return;
		}
	}
	PRINTF( "bxUserInterface::OpenMenu(): MenuDef \"%s\" does not exist\n", name.c_str() );
}


/*
=================
CloseMenu
=================
*/
void bxUserInterface::CloseMenu( std::string name )
{
	unsigned int	i, j;
	MenuDef			*menu;

	for( i = 0; i < GetNumMenus(); i++ )
	{
		menu = menuList[i];

		if( name.compare( menu->GetName() ) == 0 && menu->IsOpen() )
		{
			numOpenedMenus --;
			menu->opened = false;
			menu->active = false;


			if( menu->OnClose != 0x00000000 )
				menu->OnClose( menu );

			// activate previous menu
			for( j = GetNumMenus()-1; j != -1; j-- )
			{
				if( menuList[j]->IsOpen() && !menuList[j]->IsActive() )
					menuList[j]->active = true;
			}
			return;
		}
	}
}


/*
=================
UserInterfaceFrame

Update menus and it's elements
=================
*/

#if 0
static double lastTime = 0.0f;
#endif

void bxUserInterface::UserInterfaceFrame( double time )
{
	static unsigned int	i, j;
	MenuDef		*menu;
	ItemDef		*item;

//	if( 1 ) return;
#if 0
	if( lastTime != 0.0f && (Common->GetTime()-lastTime) < 0.05 )
		return;
	lastTime = Common->GetTime();
#endif

	if( numOpenedMenus )
	{
		Engine->p_Input->m_UpdateMousePos = true;
	//	Renderer->Ortho->drawCursor = true;
		/*if( Engine->p_Input->GetMousePos().x < 0 )
		{
			 Engine->p_Input->SetMousePos( 0, Engine->p_Input->GetMousePos().y );
		}
		else if( Engine->p_Input->GetMousePos().x > 639 )
		{
			 Engine->p_Input->SetMousePos( 639,  Engine->p_Input->GetMousePos().y );
		}

		if( Engine->p_Input->GetMousePos().y < 0 )
		{
			 Engine->p_Input->SetMousePos(  Engine->p_Input->GetMousePos().x, 0 );
		}
		else if( Engine->p_Input->GetMousePos().y > 479 ) //464
		{
			Engine->p_Input->SetMousePos( Engine->p_Input->GetMousePos().x, 479 );
		}*/
	}
	else
	{
//		Renderer->Ortho->drawCursor = false;
	}

	for( i = 0; i < GetNumMenus(); i++ )
	{
		menu = menuList[i];

		if( menu == NULL || !menu->IsOpen() || !menu->IsActive() )
			continue;

		if( menu->Update != NULL )
		{
			menu->Update( menu );
		}


		for( j = 0; j < menu->itemList.size(); j++ )
		{
			item = menu->itemList[j];
			if( item != NULL )
			{
				item->Update();
			}
		}
	}
}


void bxUserInterface::Draw()
{
	static unsigned int	i, j;
	MenuDef		*menu;
	for( i = 0; i < GetNumMenus(); i++ )
	{
		menu = menuList[i];

		if( menu == NULL || !menu->IsOpen() /*|| !menu->IsActive()*/ )
			continue;

		for( j = 0; j < menu->itemList.size(); j++ )
		{
			if( menu->itemList[j] != NULL )
			{
				menu->itemList[j]->Draw();
			}
		}
	}
}


void bxUserInterface::CleanMemory()
{
	static unsigned int i;

	MenuDef	*menu;
	for( i = 0; i < GetNumMenus(); i++ )
	{
		menu = menuList[i];
		if( menu == NULL )
			continue;

		delete menu;
//		menu = NULL;
	}
	menuList.clear();
}


unsigned int bxUserInterface::GetNumOpenedMenus()
{
	return numOpenedMenus;
}


unsigned int bxUserInterface::GetNumMenus()
{
	return menuList.size();
}


void bxUserInterface::PushMenu( MenuDef *menu )
{
	PRINTF( "Added menu: %s\n", menu->name.c_str() );
	return menuList.push_back( menu );
}
