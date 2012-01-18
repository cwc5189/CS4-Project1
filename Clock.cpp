// CLOCK.CPP
// Author:  Chad Campbell - cwc5189
// Created: 1/16/2012
// Updated: 1/17/2012

#include "Clock.h"
#include "Solver.h"
#include <iostream>
using namespace std;

// NAME: main
//
// DESCRIPTION: Driver for the program, it checks for correct
//				command line args and then if that is valid, it
//				then goes ahead and loads a clock into a solver
//				and attempts to solve it, displaying the results.
int main(int argc, char *argv[]){
	if(argc != 4 ){
		cout << "Usage: clockhrs start stop" << endl;
	}
	else{
		if(((atoi(argv[1]) < 0)) || (atoi((argv[1])) < 0) || (atoi((argv[1])) < 0)){
			cout << "Usage: clockhrs start stop" << endl;
		}
		else{
			//read args
			Clock c(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
			Solver s(c);  //Connect clock to solver
			s.solve();
			//print solution
			s.display();
		}
	}
}

// NAME: (ctor)
//
// ARGUMENTS: numHours - the hour system for the clock
//			  cTime - the current time
//			  tTime - the desired (or true) time;
//
// DESCRIPTION: A clock that stores the hour system, the current time
//              and the desired time to be set to.
Clock::Clock(int numHours, int cTime, int tTime) :
	_numHours(numHours), _cTime(cTime), _tTime(tTime){
}

	// NAME: getNeighbors
	//
	// ARGUMENTS: c - The time to get neighbors of
	//
	// RETURNS: neighbors - a vector of the two ints that neighbor c
	//
	// DESCRIPTION: returns a vector containing the two times that are
	//				one hour ahead and one hour behind the time 'c'.
	//				If c = 1, then it sets the hour preceding 1 to be
	//				12.
	vector<int> Clock::getNeighbors(int c){
		vector<int> neighbors;
		if(c == 1){
			neighbors.push_back(12);
		}
		else{
			neighbors.push_back((c - 1)%_numHours);
		}
		neighbors.push_back((c + 1)%_numHours);

		return neighbors;
		
	}

	// Simple return method for _cTime
	int Clock::cTime(){
		return _cTime;
	}

	// Simple return method for _tTime
	int Clock::tTime(){
		return _tTime;
	}
