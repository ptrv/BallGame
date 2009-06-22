/*==========================================================
	Copyright (c) Peter Vasil, 2008
 ==========================================================*/

#include "PVTimer.h"
#include <iostream>

PVTimer* PVTimer::m_instance = 0;
double PVTimer::lastTime = 0;
PVTimer::PVTimer()
{
}

PVTimer::~PVTimer()
{
}

double PVTimer::messureTime()
{
	clock_t currentTime = clock();
	double time = diffClockMs(currentTime, lastTime);
	lastTime = currentTime;
	return time;
}

double PVTimer::diffClockMs(clock_t t1, clock_t t2)
{
	double diffTicks = t1 - t2;
	double diffMs = diffTicks / 1000;
	return diffMs;
}
