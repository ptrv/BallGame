/*==========================================================
	Copyright (c) Peter Vasil, 2008
 ==========================================================*/

#include "PVTimer.h"
#include <iostream>

PVTimer* PVTimer::m_instance = 0;

PVTimer::PVTimer() : 
	lastTime(clock()),
	performanceTimer(0.0),
	performanceCount(0)
{
}

PVTimer::~PVTimer()
{
}

bool PVTimer::messureTime()
{
	clock_t currentTime = clock();
	double time = diffClockMs(currentTime, lastTime);
	lastTime = currentTime;
	performanceTimer += time;
	++performanceCount;
	
	if ( performanceTimer >= 0.03 )
	{
		//std::cout << "simulations per 0.3 miliseconds: " << performanceCount << std::endl;
		performanceTimer = 0.0;
		//performanceCount = 0;
		return true;
	}
	return false;
}

double PVTimer::diffClockMs(clock_t t1, clock_t t2)
{
	double diffTicks = t1 - t2;
	double diffMs = diffTicks / CLOCKS_PER_SEC;
	return diffMs;
}
