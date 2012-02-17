// File: $Id: clock.cpp,v 1.1 2012/01/29 01:53:35 jrl6166 Exp jrl6166 $
// Author:	 Jeff Lansing
// Description:  n/a
// Revision History:
// 	$Log: clock.cpp,v $
// 	Revision 1.1  2012/01/29 01:53:35  jrl6166
// 	Initial revision
//
// 	Revision 1.2  2012/01/24 15:04:52  jrl6166
// 	clock specific program with proper error handling
//
//

#include <cstdlib>
#include <iostream>
#include <climits>
#include "ClockPuzzle.h"

const int NUM_CLOCK_ARGS = 4;

// specialized for the clock program
// no negative or zero values are allowed here
// There is no zero hour hand on a clock
bool isValidInt(int x) {
	return x > 0 && x != INT_MIN && x != INT_MAX;
}

// Entry point for the clock program
// Does basic parsing and input validation
// Feeds said data to the solver
int main(int argc, char * argv[]) {
	int numHours, startTime, stopTime;
	if (argc == NUM_CLOCK_ARGS) {
		numHours = atoi(argv[1]);
		startTime = atoi(argv[2]);
		stopTime = atoi(argv[3]);
	} else {
		std::cout << "Invalid arguments.  Usage is clock [hours] [start] [stop]" << std::endl;
		return 1;
	}
	if (!isValidInt(numHours)) {
		std::cout << "Invalid input for hours" << std::endl;
		return 1;
	}
	if (!isValidInt(startTime)) {
		std::cout << "Invalid input for start" << std::endl;
		return 1;
	}
	if (!isValidInt(stopTime)) {
		std::cout << "Invalid input for stop" << std::endl;
		return 1;
	}
	if (startTime > numHours) {
		std::cout << "Start time cannot be greater than the number of hours on the clock!" << std::endl;
		return 1;
	}
	if (stopTime > numHours) {
		std::cout << "Stop time cannot be greater than the number of hours on the clock!" << std::endl;
		return 1;
	}
	// create and solve clock puzzle
	ClockPuzzle clockPuzzle = ClockPuzzle(numHours, startTime, stopTime);
	clockPuzzle.solve(std::cout);
	return 0;
}
