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
	if (initialize) {
		now = time(0);
		dif = Max - (now - start); // Countdown from Max to 0

		if (dif < 0) {
			dif = 0; // Ensure dif doesn't go negative
		}
	}

	return to_string(dif);
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
