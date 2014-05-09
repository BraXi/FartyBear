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

#ifndef _ITEMDEF_
#define _ITEMDEF_

#include "../Shared.h"


// ========================================================================
// Item Flags
//
// These affect rendering of items
// ========================================================================

#define ITEMFLAG_IMAGE		2
#define ITEMFLAG_BORDER		4
#define ITEMFLAG_TEXT		8



// ========================================================================
// Item Types
// ========================================================================

enum UI_ITEM_TYPE
{
	ITYPE_DEFAULT,
	ITYPE_BUTTON,
	ITYPE_DUMMY
};


// ========================================================================
// ItemDef
//
// Stores all variables used by UI elements
// ========================================================================

class ItemDef
{
public:
	ItemDef();
	ItemDef( UI_ITEM_TYPE type, int flags = 0, char *name = NULL );

	~ItemDef();

	void				Update();
	void				Draw();

	void				SetDefaults();
	void				Clear();

	bool				MouseOver( int x, int y, int w, int h );
	bool				MouseOver( vec4 rect );

public:
	UI_ITEM_TYPE		type;			// enum UI_ITEM_TYPE
	int					flags;			// ITEMFLAG_*

	bool				visible;		// don't draw & update if false
	bool				focused;		// is mouse over?

	bool				positiveDim;
	vec4				rect;			// rectangle - position, width & height
	vec4				collRect;

	float				borderSize;
	vec4				borderColor;	// rgba

	vec2				textAlign;		// enum UI_ITEM_ALIGN_HORIZONTAL
	vec4				textColor;		// rgba
	vec2				textOffset;
	float				fontSize;
	int					font;			// enum UI_FONT_TYPE

	class CTexture		*mat;			// background image
	vec4				color;			// rgba

	std::string			name;
	std::string			string;

	void				(*OnFocus)( ItemDef *self, bool state );	// called when mouse is over
	void				(*OnAction)( ItemDef *self );				// called on action
	void				(*OnSecondaryAction)( ItemDef *self );		// called on secondary right mouse button

};


#endif /*_ITEMDEF_*/
