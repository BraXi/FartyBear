///////////////////////////////////////////////////////////////
////|         |///|        |///|       |/\  \/////  ///|  |////
////|  |////  |///|  |//|  |///|  |/|  |//\  \///  ////|__|////
////|  |////  |///|  |//|  |///|  |/|  |///\  \/  /////////////
////|          |//|  |//|  |///|       |////\    //////|  |////
////|  |////|  |//|         |//|  |/|  |/////    \/////|  |////
////|  |////|  |//|  |///|  |//|  |/|  |////  /\  \////|  |////
////|  |////|  |//|  |///|  |//|  |/|  |///  ///\  \///|  |////
////|__________|//|__|///|__|//|__|/|__|//__/////\__\//|__|////
///////////////////////////////////////////////////////////////
//
// BXEngine (C) 2013 BraXi
//

#define PRAGMA_TOOLS 1

#include "ToolsCommon.h"

//#if !defined(_WIN32)
	#define KWHT  "\x1B[37m"
	#define KGRN  "\x1B[32m"
	#define KBLU  "\x1B[34m"
	#define KRED  "\x1B[31m"
	#define KYEL  "\x1B[33m"
//#endif

#include <stdarg.h>


#define MAX_ARGS 		80
#define MAX_TOKEN_CHARS		2048


 #define strcasecmp _stricmp 

class Parser
{
public:

	virtual int	NumArgs();
	virtual char	*GetArg( int arg );
	virtual char	*Args();

	virtual char	*Parse( char *data );
	virtual void	TokenizeString( char *text );

	int		argc;
	char		*argv[MAX_ARGS];
	char		token[MAX_TOKEN_CHARS];
	char		*null_string;// = "";
	char		*args;
};



int Parser::NumArgs()
{
	return argc;
}


char *Parser::GetArg( int arg )
{
	if( arg >= argc )
		return null_string;
	return argv[arg];
}


// Returns a single string containing argv(1) to argv(argc()-1)
char *Parser::Args()
{
	if( !args )
		return null_string;
	return args;
}

char *Parser::Parse( char *data )
{
	int        c;
	int        len;

	len = 0;
	token[0] = 0;

	if( !data )
		return NULL;

// skip whitespace
skipwhite:
	while( (c = *data) <= ' ' )
	{
		if( c == 0 )
			return NULL;            // end of file;
		data++;
    }

// skip // comments
	if( c=='/' && data[1] == '/' )
    {
		while( *data && *data != '\n' )
			data++;
		goto skipwhite;
    }


// handle quoted strings specially
	if( c == '\"' )
    {
		data++;
		while( 1 )
        {
			c = *data++;
			if (c=='\"' || !c)
			{
				token[len] = 0;
				return data;
			}
			token[len] = c;
			len++;
		}
	}

// parse a regular word
	do
	{
		token[len] = c;
		data++;
		len++;
		c = *data;
	} while( c > 32 );

	token[len] = 0;
	return data;
}


void Parser::TokenizeString( char *text )
{
	// "string a b c" --> "string", "a", "b", "c"
	// "lol "123 trololo"" --> "lol", "123 trololo"

	// clear the args from the last string
	memset( argv, 0, sizeof(char*)*MAX_ARGS );

	argc = 0;
	args = NULL;

	while( 1 )
	{
		// skip whitespace up to a /n
		while( *text && *text <= ' ' && *text != '\n' )
		{
			text++;
		}

		if( *text == '\n' )
		{    // a newline seperates commands in the buffer
			text++;
			break;
		}

		if( !*text )
			return;

		if( argc == 1 )
			args = text;

		text = Parse( text );

		if( !text )
			return;

		if( argc < MAX_ARGS )
        {
			argv[argc] = new char[ strlen(token)+1 ];
			strcpy( argv[argc], token );
			argc++;
        }
    }
}


char *Vec3ToString( vec3 vec )
{
	static char out[128];
	sprintf( out, "%f %f %f", vec.x, vec.y, vec.z );
	return out;
}
 
typedef struct def_s
{
	char 	*source;
	char	*outName;
	vec3	scale;
	unsigned int	anim_fps;
} def_t;

static def_t def;


bool ParseDEF( const char* name )
{
	char 	line[128];
	FILE 	*f;
	Parser 	parser;
	int	cLine = 0;

	parser.null_string = (char*)"";

	def.source = NULL;
	def.outName = NULL;
	def.scale = vec3(1,1,1);
	def.anim_fps = 25;

	if( !(f = fopen( name, "r" )) )
	{
		printf( (char*)"%sCannot open definition file \"%s\"%s\n", KRED, name, KWHT );
		return false;
	}

	while( fgets( line, sizeof(line), f ) != NULL )
	{
		cLine ++;
        	parser.TokenizeString( line );

		if( !parser.NumArgs() )
			continue;

		if( strcasecmp( "$source", parser.GetArg(0) ) == 0 )
		{
			if( parser.NumArgs() != 2 )
			{
				fclose( f );
				printf( (char*)"%s[%s (%i)]: $source must have %i values %s\n", KRED, name, cLine, 1, KWHT );
				printf( (char*)"%susage: $source <.smd file to process> %s\n", KRED, KWHT );
				return false;
			}
			def.source = new char[ strlen(parser.GetArg(1)) ];
			strcpy( def.source, parser.GetArg(1) );
		}
		else if( strcasecmp( "$name", parser.GetArg(0) ) == 0 )
		{
			if( parser.NumArgs() != 2 )
			{
				fclose( f );
				printf( (char*)"%s[%s (%i)]: $name must have %i values %s\n", KRED, name, cLine, 1, KWHT );
				printf( (char*)"%susage: $name <name (/and directory) of output file> %s\n", KRED, KWHT );
				return false;
			}
			def.outName = new char[ strlen(parser.GetArg(1)) ];
			strcpy( def.outName, parser.GetArg(1) );
		}
		else if( strcasecmp( "$scale", parser.GetArg(0) ) == 0 )
		{
			if( parser.NumArgs() != 4 )
			{
				fclose( f );
				printf( (char*)"%s[%s (%i)]: $scale must have %i values %s\n", KRED, name, cLine, 3, KWHT );
				printf( (char*)"%susage: $scale <x> <y> <z> %s\n", KRED, KWHT );
				return false;
			}

			def.scale = vec3( atof(parser.GetArg(1)), atof(parser.GetArg(2)), atof(parser.GetArg(3)) );
			
			if( !def.scale.x || !def.scale.y || !def.scale.z )
			{
				fclose( f );
				printf( (char*)"%s[%s (%i)]: $scale (%s)cannot be negative %s\n", KRED, name, cLine, Vec3ToString(def.scale), KWHT );
				return false;
			}			
		}
		else if( strcasecmp( "$anim_fps", parser.GetArg(0) ) == 0 )
		{
			if( parser.NumArgs() != 2 )
			{
				fclose( f );
				printf( (char*)"%s[%s (%i)]: $anim_fps must have %i values %s\n", KRED, name, cLine, 1, KWHT );
				printf( (char*)"%susage: $anim_fps <int> (25 default)%s\n", KRED, KWHT );
				return false;
			}

			def.anim_fps = atoi(parser.GetArg(1));
			
			if( !def.scale.x || !def.scale.y || !def.scale.z )
			{
				fclose( f );
				printf( (char*)"%s[%s (%i)]: $anim_fps cannot be negative %s\n", KRED, name, cLine, KWHT );
				return false;
			}			
		}
	}

	fclose( f );


	if( !def.source )
	{
		printf( "%s$source is empty %s\n", KRED, KWHT );
		return false;
	}
	if( !def.outName )
	{
		printf( "%s$name is empty %s\n", KRED, KWHT );
		return false;
	}

	return true;
}


enum SMD_Def
{
	SMD_VERSION,
	SMD_NODES,
	SMD_SKELETON,
	SMD_TRIANGLES,
	SMD_END
};

#include <vector>
using namespace std;

vector<mdl_bone_t*>		v_Bones;
vector<mdl_material_t*>		v_Materials;
vector<mdl_group_t*>		v_Groups;
vector<mdl_vert_t*>		v_Verts;
vector<mdl_animframe_t*>	v_AnimFrames;

bool ParseSMD( const char* name )
{
	char 	line[128];
	FILE 	*f;
	Parser 	parser;
	int	cType = -1;
	int 	cLine = 0;
	unsigned int currentMaterial = 0;

	parser.null_string = (char*)"";

	if( !(f = fopen( name, "r" )) )
	{
		printf( (char*)"%sCannot open file \"%s\"%s\n", KRED, name, KWHT );
		return false;
	}


	while( fgets( line, sizeof(line), f ) != NULL )
	{
		cLine ++;
        	parser.TokenizeString( line );

		if( !parser.NumArgs() )
            		continue;

		if( strcasecmp( parser.GetArg(0), "version" ) == 0 )
		{
			// <string> <int>
			cType = SMD_VERSION;
			continue;
		}
		else if( strcasecmp( parser.GetArg(0), "nodes" ) == 0 )
		{
			// <int> <string> <int>
			cType = SMD_NODES;
			continue;
		}
		else if( strcasecmp( parser.GetArg(0), "skeleton" ) == 0 )
		{
			cType = SMD_SKELETON;
			continue;
		}
		else if( strcasecmp( parser.GetArg(0), "triangles" ) == 0 )
		{
			cType = SMD_TRIANGLES;
			continue;
		}
		else if( strcasecmp( parser.GetArg(0), "end" ) == 0 )
		{
			if( cType == SMD_TRIANGLES )
			{
				unsigned int index = v_Groups.size()-1;
					
				v_Groups[ index ]->material = currentMaterial;
				v_Groups[ index ]->numVerts = ( v_Verts.size() - v_Groups[ index ]->firstVert );
				if( !v_Groups[ index ]->numVerts ) printf( "group %i has 0 verts\n", index );
			}

			cType = SMD_END;
			continue;
		}

		if( cType == SMD_NODES )
		{
			if( parser.NumArgs() != 3 )
			{
				fclose( f );
				printf( (char*)"%s[%s (%i)]: has %i arguments but should have %i %s\n", KYEL, name, cLine, parser.NumArgs(), 3, KWHT );
				return false;
			}
			mdl_bone_t *bone = new mdl_bone_t;


			if( strlen( parser.GetArg(1) ) >= MAX_BONE_NAME )
			{
				fclose( f );
				printf( (char*)"%s[%s (%i)]: bone name \"%s\" is too long, max length is %i%s\n", KYEL, name, cLine, parser.GetArg(1), MAX_BONE_NAME, KWHT );
				return false;				
			}

			bone->id = atoi( parser.GetArg(0) );
			strcpy( bone->name, parser.GetArg(1) );
			bone->owner = atoi( parser.GetArg(2) );

			v_Bones.push_back( bone );
			continue;
		}
		else if( cType == SMD_SKELETON )
		{

			if( strcasecmp( parser.GetArg(0), "time" ) == 0 )
			{
				if( parser.NumArgs() != 2 )
				{
					fclose( f );
					printf( (char*)"%s[%s (%i)]: has %i arguments but should have %i%s\n", KYEL, name, cLine, parser.NumArgs(), 2, KWHT );
					return false;
				}

				mdl_animframe_t *aFrame = new mdl_animframe_t;
				v_AnimFrames.push_back( aFrame );

				v_AnimFrames[ v_AnimFrames.size()-1 ]->num = atoi( parser.GetArg(1) );
				v_AnimFrames[ v_AnimFrames.size()-1 ]->bones = new mdl_animbone_t[ v_Bones.size() ];
				continue;
			}

			if( parser.NumArgs() != 7 )
			{
				fclose( f );
				printf( (char*)"%s[%s (%i)]: has %i arguments but should have %i%s\n", KYEL, name, cLine, parser.NumArgs(), 7, KWHT );
				return false;
			}
			
			unsigned int id = atoi( parser.GetArg(0) );
			int index = v_AnimFrames.size()-1;

			if( id >= v_Bones.size() )
			{
				fclose( f );
				printf( (char*)"%s[%s (%i)]: bone %i doesn't exist%s\n", KYEL, name, cLine, id, KWHT );
				return false;
			}
			
			v_AnimFrames[ index ]->bones[ id ].origin.x = (float)atof( parser.GetArg(1) );
			v_AnimFrames[ index ]->bones[ id ].origin.z = (float)atof( parser.GetArg(2) );
			v_AnimFrames[ index ]->bones[ id ].origin.y = (float)atof( parser.GetArg(3) );
			v_AnimFrames[ index ]->bones[ id ].angles.x = (float)atof( parser.GetArg(4) );
			v_AnimFrames[ index ]->bones[ id ].angles.z = (float)atof( parser.GetArg(5) );
			v_AnimFrames[ index ]->bones[ id ].angles.y = (float)atof( parser.GetArg(6) );
		}
		else if( cType == SMD_TRIANGLES )
		{
			if( parser.NumArgs() == 1 ) 
			{
				bool newGroup = false;
				unsigned int index;

				if( v_Groups.size() && strcasecmp( parser.GetArg(0), v_Materials[v_Groups[ v_Groups.size()-1 ]->material]->name ) == 0 ) continue;
				if( !v_Materials.size() )
				{
					mdl_material_t *cMaterial = new mdl_material_t;
					v_Materials.push_back( cMaterial );

					unsigned int index = v_Materials.size()-1;
					

					v_Materials[ index ]->id = index;
					// FIXME
					strcpy( v_Materials[ index ]->name, parser.GetArg(0) );

					currentMaterial = 0;
					newGroup = true;
				}
				else if( strcasecmp( v_Materials[v_Materials.size()-1]->name, parser.GetArg(0) ) != 0 )
				{
					unsigned int s = v_Materials.size()+1;
					// check if we already stored this "new" material
					for( unsigned int i = 0; i < s; i++ )
					{
						// we're dealing with new material
						if( i == v_Materials.size() )
						{
							v_Materials.push_back( new mdl_material_t );

							index = v_Materials.size()-1;
							currentMaterial = index;

							v_Materials[ index ]->id = index;
							strcpy( v_Materials[ index ]->name, parser.GetArg(0) ); 
							
							// close previous group and create new one for new material
							currentMaterial = index;
							newGroup = true;
					
							if( v_Groups.size() )
							{
								index = v_Groups.size()-1;
								v_Groups[ index ]->numVerts = ( v_Verts.size() - v_Groups[ index ]->firstVert );
							}
						}
						// otherwise we found material in database
						if( strcasecmp( v_Materials[i]->name, parser.GetArg(0) ) == 0 && v_Groups[ v_Groups.size()-1 ]->material != (int)i )
						{
							newGroup = true;
							currentMaterial = i;

							break;
						}
					}
				}

				
				if( newGroup && v_Groups.size() )
				{

					index = v_Groups.size()-1;
					v_Groups[ index ]->numVerts = ( v_Verts.size() - v_Groups[ index ]->firstVert );
					if (index != 0 )
					v_Groups[ index ]->firstVert ++;
				}

				if( !v_Groups.size() || newGroup )
				{
					//mdl_group_t *cGroup = ;
					v_Groups.push_back( new mdl_group_t );

					unsigned int index = v_Groups.size()-1;
					
					v_Groups[ index ]->material = currentMaterial; //v_Materials.size()-1;
					v_Groups[ index ]->firstVert = v_Verts.size();
				}
			}
			else if( parser.NumArgs() >= 9 ) 
			{
				mdl_vert_t *v = new mdl_vert_t;
				v_Verts.push_back( v );

				unsigned int index = v_Verts.size()-1;

				v_Verts[ index ]->boneId = atoi( parser.GetArg(0) );

				v_Verts[ index ]->origin.x = (float)atof( parser.GetArg(1) );
				v_Verts[ index ]->origin.y = (float)atof( parser.GetArg(3) );
				v_Verts[ index ]->origin.z = (float)atof( parser.GetArg(2) );

				v_Verts[ index ]->normal.x = (float)atof( parser.GetArg(4) );
				v_Verts[ index ]->normal.y = (float)atof( parser.GetArg(6) );
				v_Verts[ index ]->normal.z = (float)atof( parser.GetArg(5) );

				v_Verts[ index ]->uv.x = (float)atof( parser.GetArg(7) );
				v_Verts[ index ]->uv.y = (float)-atof( parser.GetArg(8) );

			//fscanf( f, "%s", in ); vert.uv.x = (float)atof( in );
			//fscanf( f, "%s", in ); vert.uv.y = -(float)atof( in );
			}
		}


	}

	fclose( f );

	return true;
}



void WriteAnim( const char *fileName )
{
	FILE 		*f;
	char 		outName[256];
	unsigned int	i;
	mdl_header_t	header;
	anim_info_t	info;


	sprintf( outName, "./%s.anim", fileName );

	if( !(f = fopen( outName, "wb")) )
	{
		printf( "%sCannot open \"%s\" for writing\n", KRED, outName );
		return;
	}

	header.magic = BX_ANIM_HEADER;
	header.version = BX_ANIM_VERSION;

	info.numBones = v_Bones.size();
	info.numFrames = v_AnimFrames.size();
	info.FPS = def.anim_fps;

	SafeWrite( f, &header, sizeof(mdl_header_t) );
	SafeWrite( f, &info, sizeof(anim_info_t) );

	for( i = 0; i < v_Bones.size(); i++ )
		SafeWrite( f, v_Bones[i], sizeof(mdl_bone_t) );

	for( i = 0; i < v_AnimFrames.size(); i++ )
		SafeWrite( f, v_AnimFrames[i], sizeof(mdl_animframe_t) );

	size_t total =  sizeof(header) + sizeof(info) + (v_Bones.size()*sizeof(mdl_bone_t)) + (v_AnimFrames.size()*sizeof(mdl_animframe_t));

	fclose( f );
	printf( "%sAnimation saved as: %s (%i bytes)%s\n", KGRN, outName, total, KWHT );
}

void WriteMesh( const char *fileName )
{
	FILE 		*f;
	char 		outName[256];
	unsigned int	i;
	mdl_header_t	header;
	mdl_info_t	info;


	sprintf( outName, "./%s.mdl", fileName );

	if( !(f = fopen( outName, "wb")) )
	{
		printf( "%sCannot open \"%s\" for writing\n", KRED, outName );
		return;
	}

	header.magic = BX_MESH_HEADER;
	header.version = BX_MESH_VERSION;

	info.numBones = v_Bones.size();
	info.numMaterials = v_Materials.size();
	info.numGroups = v_Groups.size();
	info.numVerts = v_Verts.size();

	SafeWrite( f, &header, sizeof(mdl_header_t) );
	SafeWrite( f, &info, sizeof(mdl_info_t) );

	//fprintf( f, "bones:\n" );
	for( i = 0; i < v_Bones.size(); i++ )
		SafeWrite( f, v_Bones[i], sizeof( mdl_bone_t ) );

//	for( i = 0; i < v_Bones.size(); i++ )
//	SafeWrite( f, v_AnimFrames[0]->bones, sizeof( *v_AnimFrames[0]->bones ) );
		
	for( i = 0; i < v_Bones.size(); i++ )
		SafeWrite( f, &v_AnimFrames[0]->bones[i], sizeof( mdl_animbone_t ) );




	for( i = 0; i < v_Materials.size(); i++ )
		SafeWrite( f, v_Materials[i], sizeof( mdl_material_t ) );

	for( i = 0; i < v_Groups.size(); i++ )
		SafeWrite( f, v_Groups[i], sizeof( mdl_group_t ) );

	for( i = 0; i < v_Verts.size(); i++ )
		SafeWrite( f, v_Verts[i], sizeof( mdl_vert_t ) );

	size_t total =  sizeof(header) + sizeof(info) + (v_Bones.size()*sizeof(mdl_bone_t)) + (v_Materials.size()*sizeof(mdl_material_t)) + (v_Groups.size()*sizeof(mdl_group_t)) + (v_Verts.size()*sizeof(mdl_vert_t)) ;

	fclose( f );
	printf( "%sModel saved as: %s (%i bytes)%s\n", KGRN, outName, total, KWHT );
}


void CalculateBoundingBox()
{
	vec3 mins;
	vec3 maxs;
	mins = maxs = vec3(0,0,0);

	for( unsigned int i = 0; i < v_Verts.size(); i++ ) 
	{
		if( v_Verts[i]->origin.x < mins.x ) mins.x = v_Verts[i]->origin.x;
		if( v_Verts[i]->origin.x > maxs.x ) maxs.x = v_Verts[i]->origin.x;

		if( v_Verts[i]->origin.y < mins.y ) mins.y = v_Verts[i]->origin.y;
		if( v_Verts[i]->origin.y > maxs.y ) maxs.y = v_Verts[i]->origin.y;

		if( v_Verts[i]->origin.z < mins.z ) mins.z = v_Verts[i]->origin.z;
		if( v_Verts[i]->origin.z > maxs.z ) maxs.z = v_Verts[i]->origin.z;
	}
	printf( "%sBounding Box dimensions: %s\n", KWHT, KYEL );
   	printf( "   Mins: (%s)\n", Vec3ToString(mins) );
	printf( "   Maxs: (%s)%s\n", Vec3ToString(maxs), KWHT );
}

#define VERSIONSTRING	( "1.2 (" __DATE__ " " __TIME__ ")" ) 
int main( int argc, char **argv )
{
	unsigned int 	i;
	bool		isAnim;

	printf( "\nModelgen %s for Unkknow Engine (c) 2013 BraXi\n\n", VERSIONSTRING );

	if( argc != 2 )
	{
		printf( "%susage: ./modelgen <.def file>\n", KRED );
		printf( "example: ./modelgen cube.def%s\n\n", KWHT );
		return 1;
	}

	printf( "Definition file: %s%s %s\n", KYEL, argv[1], KWHT );
	if( !ParseDEF( argv[1] ) )
		return 1;

	printf( "Source file: %s%s %s\n", KYEL, def.source, KWHT );
	if( !ParseSMD( def.source ) )
		return 1;

	isAnim = v_AnimFrames.size() > 1 ? true : false;


	printf( "\n" );
	if( isAnim )
	{
		printf( "%sSMD verified as animation!\n", KGRN);

		printf( "%sAnimation FPS:%s %i %s\n", KWHT, KYEL, def.anim_fps, KWHT );
	}
	else
	{
		printf( "%sSMD verified as mesh!\n", KGRN);

		printf( "%sScale to apply: %s%s %s\n", KWHT, KYEL, Vec3ToString(def.scale), KWHT );
	}


	printf( "%s\n", KYEL );
	printf( (char*)"   %i joints\n", v_Bones.size() );
	if( isAnim )
	{
		printf( (char*)"   %i frames\n", v_AnimFrames.size() );
		//printf( (char*)"   %i FPS\n", def.anim_fps );
	}
	if( !isAnim )
	{
		printf( (char*)"   %i materials\n", v_Materials.size() );
		printf( (char*)"   %i groups\n", v_Groups.size() );
		printf( (char*)"   %i vertices\n\n", v_Verts.size() );
		CalculateBoundingBox();
	}

	if( !isAnim && ( def.scale.x != 1.0f || def.scale.y != 1.0f || def.scale.z != 1.0f ) )
	{
		for( i = 0; i < v_Verts.size(); i++ )
		{
			v_Verts[i]->origin.x *= def.scale.x;
			v_Verts[i]->origin.y *= def.scale.y;
			v_Verts[i]->origin.z *= def.scale.z;
		}
	}


	printf( "%s\n", KWHT );
	for( i = 0; i < v_Bones.size(); i++ )
	{
		printf( (char*)"joint %i - \"%s\", parent of %i\n", v_Bones[i]->id, v_Bones[i]->name, v_Bones[i]->owner );
	}
	printf( "---\n" );
	if( !isAnim )
	{
		for( i = 0; i < v_Materials.size(); i++ )
		{
			printf( (char*)"material %i - \"%s\" \n", i, v_Materials[i]->name );
		}
		printf( "---\n" );
		for( i = 0; i < v_Groups.size(); i++ )
		{
			printf( (char*)"group %i - material \"%s\" {%i,%i} \n", i, v_Materials[v_Groups[i]->material]->name, v_Groups[i]->firstVert, v_Groups[i]->numVerts );
		}
		printf( (char*)"%sTip: you can minimize number of groups by merging triangles with the same material together in your modelling software.%s\n", KBLU, KWHT );
		printf( "---\n" );
	}


	if( isAnim )
		WriteAnim( def.outName );
	else
		WriteMesh( def.outName );

	system("pause");
	return 0;
}








