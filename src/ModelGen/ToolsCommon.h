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
// BXEngine (C) 2012 BraXi
//

#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#define _WINDOWS_LEAN_AND_MEAN
#endif

//#include "../Shared.h"

#include "../Renderer/model_bxmdl.h"
#include <stdarg.h>
//-------------------------------------//

void Error (char *error, ...)
{
	va_list argptr;

	printf ("\n************ ERROR ************\n");

	va_start (argptr,error);
	vprintf (error,argptr);
	va_end (argptr);
	printf ("\n");
	//system( "pause" );
	exit( 1 );
}

///////////////////
FILE *SafeOpenWrite (char *filename)
{
	FILE	*f;

	f = fopen( filename, "wb" );
	if ( !f )
		Error( (char*)"Error opening %s", filename );

	return f;
}

FILE *SafeOpenRead( char *filename )
{
	FILE	*f;
	if( !(f = fopen( filename, "rb" )) )
		Error( (char*)"Error opening %s", filename );

	return f;
}

void SafeRead( FILE *f, void *buffer, int count )
{
	if( fread( buffer, 1, count, f ) != (size_t)count )
		Error( (char*)"File read failure" );
}


void SafeWrite( FILE *f, void *buffer, int count )
{
	if( fwrite( buffer, 1, count, f ) != (size_t)count )
		Error( (char*)"File read failure" );
}




