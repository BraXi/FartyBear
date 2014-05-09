
#include "../../CGame/Game.h"
#include "../MenuList.h"
#include "../../Engine.h"

#include "../../CGame/Game.h"

MenuDef *Menu_SelectMap = NULL;

static ItemDef *score;

static void ButtonFocus( ItemDef *self, bool state );


static void OnOpen( MenuDef *self )
{

}

static void OnClose( MenuDef *self )
{
}

static void Update( MenuDef *self )
{
}



void Init_Menu_SelectMap()
{
	ItemDef    *item;
	
	Menu_SelectMap = new MenuDef( "selectmap" );
	Engine->UI->PushMenu( Menu_SelectMap );

	Menu_SelectMap->OnOpen = OnOpen;
	Menu_SelectMap->OnClose = OnClose;
	Menu_SelectMap->Update = Update;

	item = new ItemDef( ITYPE_DEFAULT, ITEMFLAG_IMAGE, "black" );
	Menu_SelectMap->PushItem( item );
	{
		item->rect = vec4( 0,0,640,480 );
		item->mat = NULL;
		item->color = vec4( 0,0,0,1 );
	}

	item = new ItemDef( ITYPE_DEFAULT, ITEMFLAG_IMAGE, "background" );
	Menu_SelectMap->PushItem( item );
	{
		item->rect = vec4( 0,0,640,480 );
		item->mat = NULL;
		item->color = vec4( 0,0,0,1 );
	}

 	item = new ItemDef( ITYPE_BUTTON, (ITEMFLAG_TEXT | ITEMFLAG_IMAGE), "back" );
	Menu_SelectMap->PushItem( item );
	{
		item->mat = NULL;
		item->color = vec4(0.1,0.1,0.1,0.4);

		item->rect = vec4( 40,230,60,20 ); 
		item->fontSize = 1.2;
		item->textOffset = vec2( 4,13 );
		item->textColor = vec4( 0.2,0.2,0.2,1.0 );

		item->font = 0;
		item->string = "TIER #1";

		item->OnFocus = ButtonFocus;
		//item->OnAction = ButtonBackAction;
		item->visible = true;
	}


}

static void ButtonFocus( ItemDef *self, bool state )
{
	if( state == false )
	{
		self->textColor = vec4( 0.92,0.92,0.92,1.0 );
	}
	else
	{
		self->textColor = vec4( 0.9,0.3,0.1,1.0 );
	}
}