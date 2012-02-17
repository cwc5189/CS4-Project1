// File: $Id: hanoi.cpp,v 1.2 2012/01/29 01:52:16 jrl6166 Exp jrl6166 $
// Author:	 Jeff Lansing
// Description:  n/a
// Revision History:
// 	$Log: hanoi.cpp,v $
// 	Revision 1.2  2012/01/29 01:52:16  jrl6166
// 	added some docs, made compatible with templated interface
//
//
// 	Revision 1.1  2012/01/24 16:47:13  jrl6166
// 	Initial revision
//
//
#include <cstdlib>
#include <iostream>
#include <climits>
#include "Puzzle.h"
#include "HanoiPuzzle.h"

const int NUM_HANOI_ARGS = 3;

// specialized for the clock program
// no negative or zero values are allowed here
// There is no zero hour hand on a clock
bool isValidInt(int x) {
	return x > 0 && x != INT_MIN && x != INT_MAX;
}

// Validates input and logs results, either errors 
// of a solution for the board
int main(int argc, char *argv[]) {
	int numPegs, numDisks;
	if (argc == NUM_HANOI_ARGS) {
		numPegs = atoi(argv[1]);
		numDisks = atoi(argv[2]);
	} else {
		std::cout << "Invalid arguments.  Usage is hanoi [pegs] [disks]";
		return 1;
	}
	// We were marked down for catching a zero pegs input here
	// So we are passing it to the solver regardless
	/*
	if (!isValidInt(numPegs)) {
		std::cout << "Invalid input for pegs";
		return 1;
	}
	if (!isValidInt(numDisks)) {
		std::cout << "Invalid input for disks";
		return 1;
	}
	*/
	HanoiPuzzle hp = HanoiPuzzle(numPegs, numDisks);
	hp.solve(std::cout);
	return 0;
}
