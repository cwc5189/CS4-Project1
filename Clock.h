// CLOCK.H
// Author:  Chad Campbell - cwc5189
// Created: 1/16/2012
// Updated: 1/17/2012

#ifndef CLOCK_H
#define CLOCK_H
#include <vector>
using namespace std;


class Clock{
public:
	Clock();
	Clock(int numHours, int cTime, int tTime);
	vector<int> getNeighbors(int c);
	int cTime();
	int tTime();
private:
	int _numHours, _cTime, _tTime;
};

#endif