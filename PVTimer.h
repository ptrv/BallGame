/*==========================================================
 Copyright (c) Peter Vasil, 2008
 ==========================================================*/
#ifndef _PVTIMER_H_
#define _PVTIMER_H_

#include <ctime>

class PVTimer
	{
	private:
		PVTimer();
		~PVTimer();
	public:
		static PVTimer& getInstance()
		{
			if ( m_instance == NULL )
			{
				m_instance = new PVTimer();
			}
			return *m_instance;
		}
		
		bool messureTime();
		double diffClockMs(clock_t t1, clock_t t2);

	private:
		static PVTimer* m_instance;
		clock_t lastTime;
		double performanceTimer;
		unsigned int performanceCount;
		unsigned int simulationsPerSec;
	};

#endif //_PVTIMER_H_

