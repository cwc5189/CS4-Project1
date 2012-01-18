// SOLVER.H
// Author:  Chad Campbell - cwc5189
// Created: 1/16/2012
// Updated: 1/17/2012

#ifndef SOLVER_H
#define SOLVER_H
#include "Clock.h"
#include <map>

class Solver{
public:
	Solver(Clock &c);
	void solve();
	void display();

private:
	Clock& _clock;
	bool _solution;
	map<int, int> backtrace;
};

#endif