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


#ifndef _MODEL_BXMDL_
#define _MODEL_BXMDL_

#include "../Shared.h"



#define MAX_BONE_NAME	24

#define BX_MESH_HEADER	(('L'<<24)+('D'<<16)+('M'<<8)+'B')
#define BX_MESH_VERSION	6

#define BX_ANIM_HEADER	(('M'<<24)+('I'<<16)+('N'<<8)+'A')
#define BX_ANIM_VERSION	1

typedef struct 
{
	int 	magic;
	int 	version;
} mdl_header_t;

typedef struct 
{
	unsigned int 	numMaterials;
	unsigned int 	numBones;
	unsigned int 	numGroups;
	unsigned int 	numVerts;

} mdl_info_t;

typedef struct 
{
	unsigned int 	numBones;
	unsigned int	numFrames;
	unsigned int	FPS;
} anim_info_t;


typedef struct
{
	int	id;
	char	name[MAX_BONE_NAME];
	int	owner;
} mdl_bone_t;


typedef struct
{
	vec3	origin;
	vec3	angles;
} mdl_animbone_t;

typedef struct
{
	int		num;
	mdl_animbone_t	*bones;
} mdl_animframe_t;

typedef struct
{
	int	id;
	char	name[64];
} mdl_material_t;

typedef struct
{
	int	material;
	int	firstVert;
	int	numVerts;
} mdl_group_t;


typedef struct
{
	// ORDER MAKES A DIFERENCE! THESE MUST BE IN SAME ORDER AS IN VBO
	vec3	origin;
	vec3	normal;
	vec2	uv;
	int	boneId;
} mdl_vert_t;


#endif /*_MODEL_BXMDL_*/
