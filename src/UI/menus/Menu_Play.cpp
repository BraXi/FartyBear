

#include "../../CGame/Game.h"
#include "../MenuList.h"
#include "../../Engine.h"

MenuDef *Menu_Play	= NULL;

static ItemDef *title = NULL;

static void ButtonFocus( ItemDef *self, bool state );
static void ButtonExitFocus( ItemDef *self, bool state );

static void ButtonPlayCampaignAction( ItemDef *self );
static void ButtonPlaySurvivalAction( ItemDef *self );
static void ButtonBackAction( ItemDef *self );



void Init_Menu_Play()
{
	Menu_Play = new MenuDef( "play" );
	Engine->UI->PushMenu( Menu_Play );

	Menu_Play->drawCursor = true;

	ItemDef    *item;


 	item = new ItemDef( ITYPE_DEFAULT, (ITEMFLAG_TEXT), "asd" );
	Menu_Play->PushItem( item );
	{
		item->rect = vec4( 0,0,0,0 );

		item->fontSize = 2.0;
		item->textOffset = vec2( 10,20 );
		item->textColor = vec4( 1,1,1,1.0 );
		item->textAlign = vec2(0,0);
		item->font = 0;
		item->string = "SELECT GAMEMODE";
	}

 	item = new ItemDef( ITYPE_BUTTON, (ITEMFLAG_BORDER  | ITEMFLAG_TEXT | ITEMFLAG_IMAGE), "PLAY-CAMPAIGN" );
	Menu_Play->PushItem( item );
	{
		item->mat = Engine->p_Renderer->PrecacheImage("ui/play_campaign", 256, 256, false );
		item->color = vec4(1);

		item->rect = vec4( 225,200,90,96 );
		item->fontSize = 1;
		item->textOffset = vec2( 45,55 );
		item->textColor = vec4( 1.0 );
		item->textAlign = vec2(1,0);
		item->borderColor = vec4(0.5,0.5,0.5,1);
		item->borderSize = 1;
		item->font = 0;
		item->string = "CAMPAIGN";

		item->OnFocus = ButtonFocus;
		item->OnAction = ButtonPlayCampaignAction;
		item->visible = true;
	}

 	item = new ItemDef( ITYPE_BUTTON, (ITEMFLAG_BORDER  | ITEMFLAG_TEXT | ITEMFLAG_IMAGE), "PLAY-SURVIVAL" );
	Menu_Play->PushItem( item );
	{
		item->mat = Engine->p_Renderer->PrecacheImage("ui/play_campaign", 256, 256, false );
		item->color = vec4(0.1,0.1,0.1,0.4);

		item->rect = vec4( 325,200,90,96 );
		item->fontSize = 1;
		item->textOffset = vec2( 45,55 );
		item->textColor = vec4( 1.0 );
		item->textAlign = vec2(1,0);
		item->borderColor = vec4(0.5,0.5,0.5,1);
		item->borderSize = 1;
		item->font = 0;
		item->string = "SURVIVAL";

		item->OnFocus = ButtonFocus;
		item->OnAction = ButtonPlaySurvivalAction;
		item->visible = true;
	}

 	item = new ItemDef( ITYPE_BUTTON, (ITEMFLAG_TEXT | ITEMFLAG_IMAGE), "back" );
	Menu_Play->PushItem( item );
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

		item->OnFocus = ButtonExitFocus;
		item->OnAction = ButtonBackAction;
		item->visible = true;
	}
}



static void ButtonFocus( ItemDef *self, bool state )
{
	if( state == false )
	{
		self->color = vec4( 0.7,0.7,0.7,1.0 );
	}
	else
	{
		self->color = vec4( 1.0 );
	}
}

static void ButtonExitFocus( ItemDef *self, bool state )
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



static void ButtonPlayCampaignAction( ItemDef *self )
{
//	Engine->UI->OpenMenu( "selectmap" );
	Engine->UI->CloseMenu( "main" );
	Engine->UI->CloseMenu( "play" );
	Game->StartLevel(0);
}

static void ButtonPlaySurvivalAction( ItemDef *self )
{
	Engine->UI->CloseMenu( "main" );
	Engine->UI->CloseMenu( "play" );
//	Game->StartLevel(0);
}


static void ButtonBackAction( ItemDef *self )
{
	//Common->ShutdownEngine();
	Engine->UI->CloseMenu( "play" );
	Engine->UI->OpenMenu( "main" );
}
