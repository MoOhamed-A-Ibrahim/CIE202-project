#pragma once
#include <ctime>
#include <iostream>
using namespace std;


class Timer
{
protected:
	time_t start;
	time_t now;
	int dif;
	int Max=100;
	bool initialize;
	int c = 0;
public:
	void Timerr(bool initialize);
	string getinsec();
	void Reset(int max);
	int getMax();
	int checktime_end;
};

