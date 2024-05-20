#pragma once
#include <ctime>
#include <iostream>
using namespace std;


class Timer
{
protected:
	time_t start;
	time_t now;
	int dif=100;
	int Max;
	bool initialize;
	int c = 0;
public:
	Timer(bool initialize);
	string getinsec();
	void Reset(int max);
};

