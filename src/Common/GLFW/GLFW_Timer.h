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

#ifndef _GLFWTIMER_
#define _GLFWTIMER_

#include "../Timer.h"

class GLFW_Timer : public CTimer
{
public:
	GLFW_Timer() {}
	virtual ~GLFW_Timer() {}

	virtual double				GetTime();
};


#endif
