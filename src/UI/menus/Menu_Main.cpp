

#include "../../CGame/Game.h"
#include "../MenuList.h"
#include "../../Engine.h"

MenuDef *Menu_Main	= NULL;

static ItemDef *title = NULL;

static void ButtonFocus( ItemDef *self, bool state );

static void ButtonPlayAction( ItemDef *self );
static void ButtonHighScoresAction( ItemDef *self );
static void ButtonExitAction( ItemDef *self );

static void Update( MenuDef *self )
{
	if( title != NULL )
		title->fontSize = (float)(3.0f + (cos( Engine->p_Timer->GetTime()/0.5f ) * 0.3f));
}

static SoundEnt *snd;

static void OnOpen( MenuDef *self )
{
	snd = Engine->p_Sound->PlaySound( "music", 0.6f, true );
}


static void OnClose( MenuDef *self )
{
	if( snd )
		snd->endTime = 0.0;
}

void Init_Menu_Main()
{
	Menu_Main = new MenuDef( "main" );
	Engine->UI->PushMenu( Menu_Main );

	Menu_Main->Update = Update;
	Menu_Main->drawCursor = true;

	Menu_Main->OnOpen = OnOpen;
	Menu_Main->OnClose = OnClose;

	ItemDef    *item;


	item = new ItemDef( ITYPE_DEFAULT, ITEMFLAG_IMAGE, "background" );
	Menu_Main->PushItem( item );
	{
		item->mat = NULL;
		item->rect = vec4( 0, 0, 640,480 );
		item->color = vec4( 0,0,0,0.4 );
		item->visible = true;
	}

 	item = new ItemDef( ITYPE_DEFAULT, (ITEMFLAG_TEXT), "asd" );
	Menu_Main->PushItem( item );
	{
		item->rect = vec4( 0,0,0,0 ); 
		
		item->fontSize = 3.0;
		item->textOffset = vec2( 320,200 );
		item->textColor = vec4( 1,1,1,1.0 );
		item->textAlign = vec2(1,0);
		item->font = 0;
		item->string = "FARTY BEAR";

		item = title;
	}


 	item = new ItemDef( ITYPE_DEFAULT, (ITEMFLAG_TEXT), "a22" );
	Menu_Main->PushItem( item );
	{
		item->rect = vec4( 0,0,0,0 ); 
		
		item->fontSize = 1;
		item->textOffset = vec2( 320,230 );
		item->textColor = vec4( 1,1,1,1.0 );
		item->textAlign = vec2(1,0);
		item->font = 0;
		item->string = "An annoying game by BraXi";

		item = title;
	}


 	item = new ItemDef( ITYPE_BUTTON, (ITEMFLAG_TEXT | ITEMFLAG_IMAGE), "play" );
	Menu_Main->PushItem( item );
	{
		item->mat = NULL;
		item->color = vec4(0.1,0.1,0.1,0.4);

		item->rect = vec4( 270,260,100,25 ); 
		item->fontSize = 1.5;
		item->textOffset = vec2( 50,17 );
		item->textColor = vec4( 0.2,0.2,0.2,1.0 );
		item->textAlign = vec2(1,0);
		item->font = 0;
		item->string = "PLAY";

		item->OnFocus = ButtonFocus;
		item->OnAction = ButtonPlayAction;
		item->visible = true;
	}

 	item = new ItemDef( ITYPE_BUTTON, (ITEMFLAG_TEXT | ITEMFLAG_IMAGE), "highscores" );
	Menu_Main->PushItem( item );
	{
		item->mat = NULL;
		item->color = vec4(0.1,0.1,0.1,0.4);

		item->rect = vec4( 270,290,100,25 ); 
		item->fontSize = 1.5;
		item->textOffset = vec2( 50,17 );
		item->textColor = vec4( 0.2,0.2,0.2,1.0 );
		item->textAlign = vec2(1,0);
		item->font = 0;
		item->string = "OPTIONS";

		item->OnFocus = ButtonFocus;
		item->OnAction = ButtonHighScoresAction;
		item->visible = true;
	}

 	item = new ItemDef( ITYPE_BUTTON, (ITEMFLAG_TEXT | ITEMFLAG_IMAGE), "exit" );
	Menu_Main->PushItem( item );
	{
		item->mat = NULL;
		item->color = vec4(0.1,0.1,0.1,0.4);

		item->rect = vec4( 270,340,100,25 ); 
		item->fontSize = 1.5;
		item->textOffset = vec2( 50,17 );
		item->textColor = vec4( 0.2,0.2,0.2,1.0 );
		item->textAlign = vec2(1,0);
		item->font = 0;
		item->string = "LEAVE GAME";

		item->OnFocus = ButtonFocus;
		item->OnAction = ButtonExitAction;
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
	Engine->UI->OpenMenu( "play" );
//	Game->StartLevel(0);
}


static void ButtonHighScoresAction( ItemDef *self )
{
}


static void ButtonExitAction( ItemDef *self )
{
	//Common->ShutdownEngine();
	Engine->UI->OpenMenu( "exit" );
}
