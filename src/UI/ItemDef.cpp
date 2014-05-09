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

#include "ItemDef.h"
#include "../Engine.h"
#include "../Renderer/Texture.h"

// ========================================================================
// Constructors
// ========================================================================

ItemDef::ItemDef()
{
	SetDefaults();
}


ItemDef::ItemDef( UI_ITEM_TYPE type, int flags, char *name )
{
	SetDefaults();

	this->name = name;		
	this->type = type;
	this->flags = flags;
}


// ========================================================================
// Destructor
// ========================================================================


ItemDef::~ItemDef()
{
	name.clear();
	string.clear();

	Clear();

	this->name = name;		
	this->type = type;
	this->flags = flags;
}



// ========================================================================
// Helpers
// ========================================================================

void ItemDef::Clear()
{
	//memset( this, 0, sizeof(this) );
}

void ItemDef::SetDefaults()
{
	Clear();

	this->name = "";
	this->visible = true;

	this->borderSize = 1.0f;
	this->borderColor = vec4(1);

	this->string = "";
	this->textColor = vec4(1);
	this->fontSize = 1;

	this->color = vec4(1);

	this->OnFocus = NULL;
	this->OnAction = NULL;
	this->OnSecondaryAction = NULL;
}



/*
=================
Update
=================
*/
void ItemDef::Update()
{
	if( !visible )
		return;

	if( rect.z > 0 && rect.w > 0 )
		positiveDim = true;
	else
		positiveDim = false;

	collRect = rect;
	Engine->p_Renderer->p_Ortho->AdjustToVirtualScreenSize( &collRect.x, &collRect.y, &collRect.z, &collRect.w );


	if( positiveDim && MouseOver( collRect ) )
		focused = true;
	else
		focused = false;
	
	if( OnFocus != NULL )
	{
		OnFocus( this, focused );
	}


	switch( type )
	{
	case ITYPE_DEFAULT:
		break;

	case ITYPE_BUTTON:
		if( focused )
		{
			if( Engine->p_Input->MouseButtonPressed(MB_LEFT) && OnAction != NULL )
			{							
				Engine->p_Sound->PlaySound( "click", 1.0f );
				OnAction( this );
				Engine->p_Input->m_MouseButtons[MB_LEFT] = false;
				focused = false;
			}
			else if( Engine->p_Input->MouseButtonPressed(MB_RIGHT) && OnSecondaryAction != NULL )
			{	
				Engine->p_Sound->PlaySound( "click", 1.0f );
				OnSecondaryAction( this );
				Engine->p_Input->m_MouseButtons[MB_RIGHT] = false;
				focused = false;
			}
		}
		break;
	}
}


void ItemDef::Draw()
{
	if( !visible )
		return;

	if( positiveDim )
	{
		// image
		if( (flags & ITEMFLAG_IMAGE) )
		{
			//Engine->p_Renderer->SetColor( this->color );
			if( mat != NULL )
			{
				mat->Bind();
				Engine->p_Renderer->p_Ortho->DrawQuad( rect, this->color );
			}
			else
			{
				Engine->p_Renderer->BindImage( 0 );
				Engine->p_Renderer->p_Ortho->DrawQuad( rect, this->color );
			}
		}
	
		// border
		if( (flags & ITEMFLAG_BORDER) )
		{
//			Engine->p_Renderer->SetColor( borderColor );

			// left line
			Engine->p_Renderer->p_Ortho->DrawQuad( vec4(rect.x-borderSize, rect.y-borderSize, borderSize, rect.w+(borderSize*2)), borderColor );
			// right line
			Engine->p_Renderer->p_Ortho->DrawQuad( vec4(rect.x+rect.z, rect.y-borderSize, borderSize, rect.w+(borderSize*2)), borderColor );
			// top line
			Engine->p_Renderer->p_Ortho->DrawQuad( vec4(rect.x, rect.y-borderSize, rect.z, borderSize), borderColor );
			// bottom line
			Engine->p_Renderer->p_Ortho->DrawQuad( vec4(rect.x, rect.y+rect.w, rect.z, borderSize), borderColor );
		}	
	}


	// string
	if( string.size() && (flags & ITEMFLAG_TEXT) )
	{
		Engine->p_Renderer->SetColor( textColor );
	//	DrawString( std::string string, float x, float y, float fontSize = 1.0f, unsigned int fontId = 0, vec2 align = vec2(0,0) );
		Engine->p_Renderer->p_Ortho->DrawString( string, rect.x+textOffset.x, rect.y+textOffset.y, fontSize, font, textAlign );
//		Engine->p_Renderer->p_Ortho->DrawString( font, rect.x+textOffset.x, rect.y+textOffset.y, (XALIGN)textAlign, fontSize, string );
	}
}


bool ItemDef::MouseOver( int x, int y, int w, int h )
{
	static vec2 point[2];
	point[0] = vec2( x, y );
	point[1] = vec2( x+w, y+h );

	if( Engine->p_Input->GetMousePos().x >= point[0].x && Engine->p_Input->GetMousePos().y >= point[0].y && Engine->p_Input->GetMousePos().x <= point[1].x && Engine->p_Input->GetMousePos().y <= point[1].y )
		return true;
	return false;
}

bool ItemDef::MouseOver( vec4 rect )
{
	return MouseOver( (int)rect.x, (int)rect.y, (int)rect.z, (int)rect.w );
}