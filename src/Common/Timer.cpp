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

#include "../Shared.h"
#include "Timer.h"


CTimer::CTimer()
{
	newTime = deltaTime = oldTime = totalTime = 0.0f;
}

CTimer::~CTimer()
{
	newTime = deltaTime = oldTime = totalTime = 0.0f;
}


void CTimer::UpdateTime()
{
    newTime = GetTime();
    deltaTime = newTime - oldTime;
    oldTime = newTime;
	totalTime += deltaTime;
}


double CTimer::GetTimePassed()
{
    return deltaTime;
}

double CTimer::GetTotalTime()
{
	return totalTime;
}
