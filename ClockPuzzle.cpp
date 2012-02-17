// File: $Id: ClockPuzzle.cpp,v 1.1 2012/01/29 01:55:34 jrl6166 Exp jrl6166 $
// Author:	 Jeff Lansing
// Description:  ClockPuzzle implementation
// Revision History:
// 	$Log: ClockPuzzle.cpp,v $
// 	Revision 1.2  2012/01/29 01:55:34  jrl6166
// 	cleaned up code, made the config an int instead of a vector of ints
//
// 	Revision 1.1  2012/01/24 15:02:49  jrl6166
// 	Initial revision
//
//

#include "ClockPuzzle.h"

const std::string ClockPuzzle::CLOCK_PUZZLE_NAME = "Clock Puzzle";

ClockPuzzle::ClockPuzzle(int nHours, int tStart, int tEnd) : numHours(nHours), timeStart(tStart), timeEnd(tEnd) {

}

ClockPuzzle::~ClockPuzzle(void) {

}

const ClockBoardConfig& ClockPuzzle::getStart() const {
	return timeStart;
}

bool ClockPuzzle::isSolution(const ClockBoardConfig& board) const {
	return (board == timeEnd);
}

void ClockPuzzle::getNeighbors(const ClockBoardConfig& board, std::vector<ClockBoardConfig>& neighbors) const {
	ClockBoardConfig next, prev;
	next = board + 1;
	if (next > numHours)
		next = 1;
	prev = board - 1;
	if (prev < 1)
		prev = numHours;
	neighbors.push_back(next);
	neighbors.push_back(prev);
}

void ClockPuzzle::display(const ClockBoardConfig& board, std::stringstream& output, int step) const {
	output << "Step " << step << ": " << board << " O'Clock";
}

const std::string& ClockPuzzle::getName(void) const {
	return CLOCK_PUZZLE_NAME;
}
