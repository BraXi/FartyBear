
#ifndef _SHARED_H_
#define _SHARED_H_

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

#define PRINTF printf
#define FATAL_ERROR printf

#define BUFFER_OFFSET(i) (reinterpret_cast<void*>(i))

#ifdef _DEBUG
	const std::string GAME_DIR = "D:/Unkknow/build/"; //"D:/Unkknow/msvc10/Debug/";
#else
	const std::string GAME_DIR = "/home/braxi/Pulpit/Unkknow/build_stable/";
#endif

#include <glm/glm.hpp>                      // glm::vec3, glm::vec4, glm::ivec4, glm::mat4
//#include <glm/gtc/matrix_projection.hpp>    // glm::perspective
#include <glm/gtc/matrix_transform.hpp>     // glm::translate, glm::rotate, glm::scale
#include <glm/gtc/type_ptr.hpp>             // glm::value_ptr

#define vec2 glm::vec2
#define vec3 glm::vec3
#define vec4 glm::vec4
#define mat3 glm::mat3
#define mat4 glm::mat4


#ifdef _WIN32 // na linuxie jest inna nazwa tej funkcji
    #define strcasecmp _stricmp
#endif

#ifndef byte
	typedef unsigned char byte;
#endif

#endif
