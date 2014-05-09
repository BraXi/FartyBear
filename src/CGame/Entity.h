/*
===========================================================================

Unkknow Engine Source Code

Copyright (C) 2014 BraXi.
All rights reserved.

This file is part of the Unkknow Engine Source Code ("Unkknow Engine Source Code").

Contact email: thebraxi@o2.pl
Contact website: http://www.braxi.org

===========================================================================
*/

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "../Shared.h"
#include <vector>

class Box
{
public:
    vec3 m_center;
    vec3 m_extent;

    Box(){}
    Box( const vec3& center, const vec3& extent )  : m_center(center), m_extent(extent) {}

    bool Overlaps( Box *b ) const
    {
        return ::fabs(m_center[0] - b->m_center[0]) <= m_extent[0] + b->m_extent[0] &&
               ::fabs(m_center[1] - b->m_center[1]) <= m_extent[1] + b->m_extent[1] &&
               ::fabs(m_center[2] - b->m_center[2]) <= m_extent[2] + b->m_extent[2];
    }
};


const int MOVETYPE_NONE = 0;
const int MOVETYPE_VELOCITY = 2;
const int MOVETYPE_GRAVITY = 4;

class CEntity
{
public:
	CEntity();
	~CEntity();

	void					Run( double delta );

public:
	std::string				className;
	
	vec3					m_Origin, m_Velocity;
	vec3					m_Angles;

	unsigned int			m_MoveType;

	class BXMesh			*p_Model;
	vec4					m_Color;
	vec3					m_Scale;

	std::vector<Box*>		v_CollBoxes;

public:
	void					(*p_Think)(CEntity *self);
	void					(*p_OnTouch)( CEntity *self, CEntity *other );
};

#endif