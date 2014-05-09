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

#include "GLFW_Timer.h"

#include <GLFW/glfw3.h>

double GLFW_Timer::GetTime()
{
	return glfwGetTime();
}
