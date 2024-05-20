#include "Timer.h"
#include <string>

Timer::Timer(bool initialize)
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
		dif = now - start;

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
	start = 0;
}
