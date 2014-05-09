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

/*
	@FIXME: ENDIAN DEPENDANT
*/

//#define USE_MATERIALS

#include <GL/glew.h>

#include "BXMesh.h"
#include "../Shared.h"
#include "Renderer.h"
//#include "../FileSystem.h"
#include "../Renderer/ogl2/VertexBufferObject.h"

#include "../Engine.h"
#include "../Renderer/Texture.h"

#if defined( USE_MATERIALS )
	#include "../Renderer/Material.h"
#endif


// constructor
BXMesh::BXMesh( std::string name )
{
	Load( name );
}

// destructor
BXMesh::~BXMesh()
{
	name.clear();

	if( p_VertexBuffer != NULL )
	{
		delete p_VertexBuffer;
	}
}

bool BXMesh::Load( std::string fname )
{
	FILE			*f = NULL;
	mdl_header_t    header;
    unsigned int    index;

	name = fname;
	std::string modelName( GAME_DIR + "models/" + fname + ".mdl" );

	if( !(f = fopen( modelName.c_str(), "rb" ) ) )
    {
		PRINTF( "Could not find model: %s\n", modelName.c_str()  );
		return false;
    }

	fread( &header, sizeof(mdl_header_t), 1, f );

    if( header.magic != BX_MESH_HEADER )
    {
       // Com_Warning( va( "%s is not a vaild model\n", modelName ) );
        return false;
    }
    if( header.version != BX_MESH_VERSION )
    {
      //  Com_Warning( va( "BXMesh::Load(): %s is not a vaild model\n", modelName ) );
        return false;
    }

	fread( &info, sizeof(mdl_info_t), 1, f );
    if( !info.numBones )
    {
       // Com_Warning( va( "BXMesh::Load(): %s doesn't have joints\n", modelName ) );
        return false;
    }
    else if( !info.numGroups )
    {
       // Com_Warning( va( "BXMesh::Load(): %s doesn't have groups\n", modelName ) );
        return false;
    }
    else if( !info.numMaterials )
    {
       // Com_Warning( va( "BXMesh::Load(): %s doesn't have materials\n", modelName ) );
        return false;
    }
    else if( 3 > info.numVerts )
    {
       // Com_Warning( va( "BXMesh::Load(): %s must have at least 3 vertices\n", modelName ) );
        return false;
    }


    p_Joints = new mdl_bone_t[ info.numBones ];
	fread( p_Joints, sizeof(mdl_bone_t), info.numBones, f );

    p_JointsData = new mdl_animbone_t[ info.numBones ];
	fread( p_JointsData, sizeof( mdl_animbone_t ), info.numBones, f );
    //Common->FileSystem->Read( f, p_JointsData, sizeof( mdl_animbone_t ) * info.numBones );

    mdl_material_t *p_MeshMaterials = new mdl_material_t[ info.numMaterials ];
	fread( p_MeshMaterials, sizeof( mdl_material_t ), info.numMaterials, f );
   // Common->FileSystem->Read( f, p_MeshMaterials, sizeof( mdl_material_t ) * info.numMaterials );

    for( index = 0; index < info.numMaterials; index++ )
    {
        // FIXME tag
		v_Textures.push_back( Engine->p_Renderer->PrecacheImage( p_MeshMaterials[index].name ) );
    }
    delete [] p_MeshMaterials;

    p_Groups = new mdl_group_t[ info.numGroups ];
	fread( p_Groups, sizeof( mdl_group_t ), info.numGroups, f );
   // Common->FileSystem->Read( f, p_Groups, sizeof( mdl_group_t ) * info.numGroups );

    p_Vertices = new mdl_vert_t[ info.numVerts ];
	fread( p_Vertices, sizeof( mdl_vert_t ), info.numVerts, f );
    //Common->FileSystem->Read( f, p_Vertices, sizeof( mdl_vert_t ) * info.numVerts );

    fclose( f );

    if( Engine && Engine->p_Renderer )
    {
        // Upload geometry to GPU
        vertex_t *p_VBOVerts = new vertex_t[ info.numVerts ];
        for( index = 0; index < info.numVerts; index++ )
        {
            memcpy( &p_VBOVerts[index].origin, &p_Vertices[index].origin, sizeof( vec3 ) );
            memcpy( &p_VBOVerts[index].normal, &p_Vertices[index].normal, sizeof( vec3 ) );
            memcpy( &p_VBOVerts[index].uv, &p_Vertices[index].uv, sizeof( vec2 ) );
        }

        p_VertexBuffer = new VertexBufferObject( VBO_TRIS, p_VBOVerts, info.numVerts );
        delete [] p_VBOVerts;
    }

	PRINTF( "Loaded: %s\n", modelName.c_str() );

	loaded = true;
	return true;

}



bool BXMesh::IsLoaded()
{
	return loaded;
}


std::string BXMesh::GetName()
{
	return name;
}


int BXMesh::GetTag( const char *tagName )
{
	for( unsigned int i = 0; i < info.numBones; i++ )
	{
		if( strcasecmp( p_Joints[i].name, tagName ) == 0 )
			return p_Joints[i].id;
	}
	return -1;
}


vec3 BXMesh::GetTagOrigin( const char *tagName )
{
	int boneID;
    if( (boneID = GetTag( tagName )) == -1 )
		return vec3(0,0,0);
	return p_JointsData[boneID].origin;
}

vec3 BXMesh::GetTagAngles( const char *tagName )
{
	int boneID;
    if( (boneID = GetTag( tagName )) == -1 )
		return vec3(0,0,0);
	return p_JointsData[boneID].angles;
}

int BXMesh::GetTagOwner( const char *tagName )
{
	int boneID;
    if( (boneID = GetTag( tagName )) == -1 )
		return -1;
	return p_Joints[boneID].owner;
}

bool BXMesh::HasTag( const char *tagName )
{
	return ( (GetTag( tagName ) >= 0) ? true : false );
}


void BXMesh::Render( bool useMaterials )
{
	if( useMaterials )
	{
		for( unsigned int i = 0; i < info.numGroups; i++ )
		{
			if( v_Textures[ p_Groups[i].material ] != NULL )
				v_Textures[ p_Groups[i].material ]->Bind();
			else
				Engine->p_Renderer->BindImage(0);
            //p_VertexBuffer->Render( 0, info.numVerts );
			p_VertexBuffer->Render( p_Groups[i].firstVert, p_Groups[i].numVerts );
		}
	}
	else
	{
		p_VertexBuffer->Render( 0, info.numVerts );
	}

}
