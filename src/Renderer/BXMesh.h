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





#ifndef _BXMESH_
#define _BXMESH_

#include "../Shared.h"
#include "model_bxmdl.h"
#include <vector>

class BXMesh
{
public:
	BXMesh() {}
	BXMesh( std::string name );
	virtual ~BXMesh();

	bool				Load( std::string fname );

	// Returns true if model was succesfully loaded
	virtual bool		IsLoaded();

	// Renders static model
	virtual void		Render( bool useMaterials = true );

	// Returns name of the model
	virtual std::string	GetName();

	// Returns true if tag is present in model, false otherwise
	virtual bool		HasTag( const char *tagName );

	// Returns local origin vector of a bone
	virtual vec3		GetTagOrigin( const char *tagName );

	// Returns local angles of a bone
	virtual vec3		GetTagAngles( const char *tagName );

	// Returns ID of a bone, -1 if bone not found
	virtual int			GetTag( const char *tagName );

	// Returns ID of owner bone, -1 is root bone, -2 means bone is not present
	virtual int			GetTagOwner( const char *tagName );

private:
	std::string			name;
	bool				loaded;

    mdl_info_t          info;

    mdl_bone_t          *p_Joints;
    mdl_animbone_t      *p_JointsData;
	std::vector<class CTexture*> v_Textures;
	mdl_group_t         *p_Groups;
    mdl_vert_t          *p_Vertices;

	class VertexBufferObject	*p_VertexBuffer;

//	mdl_bone_t			*GetTag( const char *tagName );
};


#endif
