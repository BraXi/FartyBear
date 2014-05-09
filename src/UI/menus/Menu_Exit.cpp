
#include "../../CGame/Game.h"
#include "../MenuList.h"
#include "../../Engine.h"

static void ButtonFocus( ItemDef *self, bool state );
static void ButtonYesAction( ItemDef *self );
static void ButtonNoAction( ItemDef *self );

MenuDef *Menu_Exit = NULL;


void Init_Menu_Exit()
{
	ItemDef    *item;
	
	Menu_Exit = new MenuDef( "exit" );
	Engine->UI->PushMenu( Menu_Exit );

	item = new ItemDef( ITYPE_DEFAULT, ITEMFLAG_IMAGE, "background" );
	Menu_Exit->PushItem( item );
	{
		item->rect = vec4( 0,0,640,480 );
		item->mat = NULL;
		item->color = vec4( 0,0,0,0.7 );
	}
	

	item = new ItemDef( ITYPE_DEFAULT, (ITEMFLAG_BORDER|ITEMFLAG_IMAGE), "window" );
	Menu_Exit->PushItem( item );
	{
		item->rect = vec4( 170,140,300,200 );
		item->mat = NULL;
		item->color = vec4( 0.1,0.1,0.1,0.7 );
		item->borderSize = 1.0f;
		item->borderColor = vec4( 1.0,0.5,0.1,0.9 );
	}


	item = new ItemDef( ITYPE_DEFAULT, ITEMFLAG_TEXT, "question" );
	Menu_Exit->PushItem( item );
	{
		item->rect = vec4( 320,196,0,0 );
		item->textColor = vec4( 1,1,1,0.8 );
		item->textAlign = vec2(1,0);
		item->font = 0;
		item->string = "ARE YOU MAD ENOUGH TO RAGEQUIT?";
	}

	item = new ItemDef( ITYPE_BUTTON, (ITEMFLAG_IMAGE|ITEMFLAG_TEXT), "button-yes" );
	Menu_Exit->PushItem( item );
	{
		item->rect = vec4( 225,240,90,40 );
		item->mat = NULL;
		
		item->color = vec4(0.1,0.1,0.1,0.4);
		item->textColor = vec4( 1,1,1,0.8 );
		item->textOffset = vec2( 45,25 );
		item->fontSize = 1.3f;
		item->textAlign = vec2(1,0);
		item->font = 0;
		item->string = "YES";

		item->OnFocus = ButtonFocus;
		item->OnAction = ButtonYesAction;

		item->visible = true;
	}
	
	item = new ItemDef( ITYPE_BUTTON, (ITEMFLAG_IMAGE|ITEMFLAG_TEXT), "button-no" );
	Menu_Exit->PushItem( item );
	{
		item->rect = vec4( 325,240,90,40 );
		item->mat = NULL;
		
		item->color = vec4(0.1,0.1,0.1,0.4);
		item->textColor = vec4( 1,1,1,0.8 );
		item->textOffset = vec2( 45,25 );
		item->fontSize = 1.3f;
		item->textAlign = vec2(1,0);
		item->font = 0;
		item->string = "NO";

		item->OnFocus = ButtonFocus;
		item->OnAction = ButtonNoAction;

		item->visible = true;
	}
}


void ButtonYesAction( ItemDef *self )
{
	Engine->Shutdown();
}

void ButtonNoAction( ItemDef *self )
{
	Engine->UI->CloseMenu( "exit" );
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