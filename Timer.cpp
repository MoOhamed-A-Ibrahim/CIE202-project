#include "Timer.h"
#include <string>

void Timer::Timerr(bool initialize)
{
	this->initialize = initialize;
	dif = 0;
}

string Timer::getinsec()
{

	if (initialize && c == 0)
	{
		start = time(0);
		c += 1;
	}
	if (initialize)
	{

		now = time(0);
		if( Max >= dif)
			dif = (now - start);
		else
		{
			dif = 0;
		}

	}
	//if (dif < 10)
	//{
	//	return to_string(Max-dif);
	//}
	//if (dif < 100)
	//{
	//	return to_string(Max-dif);
	//}
	return to_string(Max-dif);
}


void Timer::Reset(int max)
{
	this->Max = max;
	dif = 0;
	start = time(0);
}

int Timer::getMax()
{
	return Max;
}
