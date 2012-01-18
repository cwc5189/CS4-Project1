// SOLVER.CPP
// Author:  Chad Campbell - cwc5189
// Created: 1/16/2012
// Updated: 1/17/2012

#include "Solver.h"
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

// NAME: (ctor)
//
// ARGUMENTS: Clock &c - The clock that this solver will solve.
//
// DESCRIPTION: Constructor for Solver that takes a clock as an argument.


Solver::Solver(Clock &c) :
	_clock(c){
}

// NAME: solve
//
// DESCRIPTION: Takes the puzzle that was entered as an argument to this
//				solver object and does a breadth first search to find
//				the steps from the current cfg to the desired cfg. Then
//				loads those steps into a map. If no solution was found
//				then it identifies that it did not find a solution.

void Solver::solve(){   
	//Make empty queue
	queue<int> queue;
	
	// Add initial cfg to front of queue
	queue.push(_clock.cTime());
	backtrace.insert(pair<int,int>(_clock.cTime(),0));

	//Loop while the queue is not empty and the front does not equal the final cfg
	while(!queue.empty() && (queue.front() != _clock.tTime())){
		// Set cfg to current front of queue and pop it off
		int cfg = queue.front();
		queue.pop();

		// Get the neighbors of current cfg
		vector<int> neighbors = _clock.getNeighbors(cfg);
		
		// Add the neighbors to the back of queue and map if they dont already exist
		if(backtrace.find(neighbors.at(0)) == backtrace.end()){
			queue.push(neighbors.at(0));
			backtrace.insert(pair<int,int>(neighbors.at(0),cfg));
		}
		if(backtrace.find(neighbors.at(1)) == backtrace.end()){
			queue.push(neighbors.at(1));
			backtrace.insert(pair<int,int>(neighbors.at(1),cfg));
		}
	}
	if(queue.empty()){
		_solution = false;
	}
	else{
		_solution = true;
	}
}

// NAME: display
//
// DESCRIPTION: Prints out the steps taken from the current cfg
//				to the desired cfg. Or if there is no solution,
//				it outputs that.
void Solver::display(){
	if(!_solution){
		cout << "There is no solution..." << endl;
	}
	else{
		// Put values from the map onto a stack
		stack<int> backpath;
		int c = _clock.tTime();
		while(c != _clock.cTime()){
			backpath.push(c);
			c = backtrace[c];
		}
		backpath.push(_clock.cTime());

		// Go through the stack of steps, numbering as you go through
		for(int i = 1; !backpath.empty(); i++){
			cout << "Step #" << i << ": ";
			cout << "Set to " << backpath.top() << " o'clock." << endl;
			backpath.pop();
		}
	}
}