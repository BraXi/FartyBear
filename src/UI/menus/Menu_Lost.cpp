
#include "../../CGame/Game.h"
#include "../MenuList.h"
#include "../../Engine.h"

#include "../../CGame/Game.h"

MenuDef *Menu_Lost = NULL;

static ItemDef *score;

static void ButtonFocus( ItemDef *self, bool state );
static void ButtonYesAction( ItemDef *self )
{
	Engine->UI->CloseMenu( "lost" );
	Game->FastRestart();
}

static void ButtonNoAction( ItemDef *self )
{
	Engine->UI->CloseMenu( "lost" );
	Game->DropGame();
	Engine->UI->OpenMenu( "main" );
}

static std::string info;

//template <typename T> std::string tostr(const T& t) { ostringstream os; os<<t; return os.str(); }

static void OnOpen( MenuDef *self )
{
	int seconds = Game->level.time / 1;

	char c[30];
	sprintf(c, "%d", seconds);

	info.clear();
	info.append( "you fell after " );
	info.append( c );
	info.append( " seconds" );

	score->string = info;
	//Game->level.time;
}


void Init_Menu_Lost()
{
	ItemDef    *item;

	Menu_Lost = new MenuDef( "lost" );
	Engine->UI->PushMenu( Menu_Lost );

	Menu_Lost->OnOpen = OnOpen;


	item = new ItemDef( ITYPE_DEFAULT, ITEMFLAG_IMAGE, "background" );
	Menu_Lost->PushItem( item );
	{
		item->rect = vec4( 0,0,640,480 );
		item->mat = NULL;
		item->color = vec4( 0,0,0,0.4 );
	}


	item = new ItemDef( ITYPE_DEFAULT, ITEMFLAG_TEXT, "as" );
	Menu_Lost->PushItem( item );
	{
		item->rect = vec4( 320,170,0,0 );
		item->textColor = vec4( 0.8,0,0,1.0 );
		item->textAlign = vec2(1,0);
		item->fontSize = 2.6f;

		item->font = 0;
		item->string = "Y O U  L O S T";
	}

	item = new ItemDef( ITYPE_DEFAULT, ITEMFLAG_TEXT, "as" );
	Menu_Lost->PushItem( item );
	{
		item->rect = vec4( 320,190,0,0 );
		item->textColor = vec4( 0.96,0.96,0.96,1 );
		item->textAlign = vec2(1,0);
		item->fontSize = 1.3f;

		item->font = 0;
		//item->string = info;//"WANT TO FART AGAIN?";

		score = item;
	}

	item = new ItemDef( ITYPE_BUTTON, (ITEMFLAG_IMAGE|ITEMFLAG_TEXT), "button-yes" );
	Menu_Lost->PushItem( item );
	{
		item->rect = vec4( 225,230,90,40 );
		item->mat = NULL;

		item->color = vec4(0.1,0.1,0.1,0.4);
		item->textColor = vec4( 0.92,0.92,0.92,1.0 );
		item->textOffset = vec2( 45,25 );
		item->fontSize = 1.3f;
		item->textAlign = vec2(1,0);
		item->font = 0;
		item->string = "RETRY";

		item->OnFocus = ButtonFocus;
		item->OnAction = ButtonYesAction;

		item->visible = true;
	}

	item = new ItemDef( ITYPE_BUTTON, (ITEMFLAG_IMAGE|ITEMFLAG_TEXT), "button-no" );
	Menu_Lost->PushItem( item );
	{
		item->rect = vec4( 325,230,90,40 );
		item->mat = NULL;

		item->color = vec4(0.1,0.1,0.1,0.4);
		item->textColor = vec4( 0.92,0.92,0.92,1.0 );
		item->textOffset = vec2( 45,25 );
		item->fontSize = 1.3f;
		item->textAlign = vec2(1,0);
		item->font = 0;
		item->string = "LEAVE";

		item->OnFocus = ButtonFocus;
		item->OnAction = ButtonNoAction;

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
