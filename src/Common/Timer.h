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

#ifndef _TIMER_
#define _TIMER_

class CTimer
{
public:
	CTimer();
	~CTimer();

	// Update timer
	void				UpdateTime();

	// Return delta
	double				GetTimePassed();

	// Get current time
	virtual double		GetTime() = 0;

	// Get elapsed time
	double				GetTotalTime();

private:
	double				newTime, deltaTime, oldTime, totalTime;
};


#endif /*_TIMER_*/
