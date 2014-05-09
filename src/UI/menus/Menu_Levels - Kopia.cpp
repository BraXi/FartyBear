

#include "../../CGame/Game.h"
#include "../MenuList.h"
#include "../../Engine.h"

MenuDef *Menu_Levels	= NULL;

static ItemDef *title = NULL;

static void ButtonFocus( ItemDef *self, bool state );

static void ButtonPlayAction( ItemDef *self );
static void ButtonBackAction( ItemDef *self );

int selectedLevel = 0;

typedef struct tier_s
{
	unsigned int tier;
	unsigned int levels[5];
} tier_t;

tier_t tiers[5];

static ItemDef *Level( std::string name, unsigned int level, int x, int y )
{
 	ItemDef *item = new ItemDef( ITYPE_BUTTON, (ITEMFLAG_BORDER|ITEMFLAG_IMAGE), "back" );
	Menu_Levels->PushItem( item );
	{
		item->mat = NULL;
		item->color = vec4(0.1,0.1,0.1,0.4);

		item->rect = vec4( x,y,32,40 ); 

		item->borderColor = vec4( 1.0,0.5,0.1,0 );
		item->borderSize = 1;

		//item->OnFocus = ButtonFocus;
		item->OnAction = ButtonBackAction;
		item->visible = true;
	}
	return item;
}


static void Tier( std::string name, int oX, int oY )
{
	ItemDef *item;

 	item = new ItemDef( ITYPE_DEFAULT, (ITEMFLAG_BORDER|ITEMFLAG_IMAGE), "title" );
	Menu_Levels->PushItem( item );
	{
		item->mat = NULL;
		item->color = vec4(0.1,0.1,0.1,0.7 );
		item->rect = vec4( oX,oY,44,260 ); 

		item->borderColor = vec4(1);
		item->borderSize = 1;
		item->visible = true;
	}

//	25


 	item = new ItemDef( ITYPE_DEFAULT, (ITEMFLAG_IMAGE|ITEMFLAG_TEXT), "title" );
	Menu_Levels->PushItem( item );
	{
		item->mat = NULL;
		item->color = vec4(0.2,0.2,0.2,0.5);
		item->rect = vec4( oX,oY+5,44,15 ); 
		item->fontSize = 1;
		item->font = 0;
		item->string = name;
		item->textOffset = vec2(22,11);
		item->textAlign = vec2(1,0);
		item->visible = true;
	}

	oY -= 1;
	Level( "0", 0, oX+6, oY+30 +(46*0) );
	Level( "1", 0, oX+6, oY+30 +(46*1) );
	Level( "2", 0, oX+6, oY+30 +(46*2) );
	Level( "3", 0, oX+6, oY+30 +(46*3) );
	Level( "4", 0, oX+6, oY+30 +(46*4) );
}
void Init_Menu_Levels()
{
	Menu_Levels = new MenuDef( "levels" );
	Engine->UI->PushMenu( Menu_Levels );

	Menu_Levels->drawCursor = true;

	ItemDef    *item;

/*	item = new ItemDef( ITYPE_DEFAULT, ITEMFLAG_IMAGE, "background" );
	Menu_Levels->PushItem( item );
	{
		item->mat = NULL;
		item->rect = vec4( 0, 0, 640,480 );
		item->color = vec4(0.1,0.2,0.42,1);
		item->visible = true;
	}
*/

 	item = new ItemDef( ITYPE_DEFAULT, (ITEMFLAG_TEXT), "back" );
	Menu_Levels->PushItem( item );
	{
		item->mat = NULL;

		item->rect = vec4( 320,75,0,0 ); 

		item->fontSize = 2;
		item->textColor = vec4( 0.8,0.8,0.8,1.0 );
		item->textAlign = vec2(1,0);
		item->font = 0;
		item->string = "SELECT LEVEL";

		item->visible = true;
	}

	item = new ItemDef( ITYPE_DEFAULT, ITEMFLAG_IMAGE, "background" );
	Menu_Levels->PushItem( item );
	{
		item->mat = NULL;
		item->rect = vec4( 114, 110, 411,280 );
		item->color = vec4(0,0,0,0.2);
		item->visible = true;
	}

	// 435
	//217
	Tier( "TIER #1", 123+(87*0), 120 );
	Tier( "TIER #2", 123+(87*1), 120 );
	Tier( "TIER #3", 123+(87*2), 120 );
	Tier( "TIER #4", 123+(87*3), 120 );
	Tier( "TIER #5", 123+(87*4), 120 );
	//235, 117.5
 	item = new ItemDef( ITYPE_BUTTON, (ITEMFLAG_TEXT | ITEMFLAG_IMAGE), "back" );
	Menu_Levels->PushItem( item );
	{
		item->mat = NULL;
		item->color = vec4(0.1,0.1,0.1,0.4);

		item->rect = vec4( 20,430,100,25 ); 
		item->fontSize = 1.5;
		item->textOffset = vec2( 50,17 );
		item->textColor = vec4( 0.2,0.2,0.2,1.0 );
		item->textAlign = vec2(1,0);
		item->borderColor = vec4(0.6,0.6,0.6,0.9);
		item->borderSize = 1;
		item->font = 0;
		item->string = "BACK";

		item->OnFocus = ButtonFocus;
		item->OnAction = ButtonBackAction;
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


static void ButtonPlayAction( ItemDef *self )
{
	Engine->UI->CloseMenu( "main" );
	//UserInterface->OpenMenu( "connect" );
	Game->StartLevel(0);
}



static void ButtonBackAction( ItemDef *self )
{
	//Common->ShutdownEngine();
	Engine->UI->CloseMenu( "levels" );
	Engine->UI->OpenMenu( "main" );
}
