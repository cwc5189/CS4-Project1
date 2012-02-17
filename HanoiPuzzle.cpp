// File: $Id: HanoiPuzzle.cpp,v 1.2 2012/01/27 00:33:21 jrl6166 Exp jrl6166 $
// Author:	 Jeff Lansing
// Description:  n/a
// Revision History:
// 	$Log: HanoiPuzzle.cpp,v $
// 	Revision 1.2  2012/01/27 00:33:21  jrl6166
// 	cleans up dynamically allocated LUT in destructor
//
// 	Revision 1.1  2012/01/24 16:48:21  jrl6166
// 	Initial revision
//
//


#include "HanoiPuzzle.h"
#include <iostream>

const std::string HanoiPuzzle::HANOI_PUZZLE_NAME = "Hanoi Puzzle";

HanoiPuzzle::HanoiPuzzle(int nPegs, int nDisks) : numPegs(nPegs), numDisks(nDisks) {
	int i;
	for (i = 0; i < nDisks; ++i) {
		start.push_back(0);
	}
	pegLookupTable = new int[nPegs];
}

HanoiPuzzle::~HanoiPuzzle(void) {
	delete [] pegLookupTable;
}

const HanoiBoardConfig& HanoiPuzzle::getStart() const {
	return start;
}

void HanoiPuzzle::getNeighbors(const HanoiBoardConfig& board, std::vector<HanoiBoardConfig>& neighbors) const {
	int i, t, top;
	for (i = 0; i < numPegs; ++i) {
		pegLookupTable[i] = -1;	// -1 means unoccupied peg
	}
	for (i = 0; i < numDisks; ++i) {
		top = pegLookupTable[board[i]]; 
		if (top == -1 || top > i) top = i; // otherwise the top of the peg 
		pegLookupTable[board[i]] = top; // is inserted  into the LUT
	}
	// knowing the top of each peg, attempt moves
	// onto larger disks or onto empty pegs
	for (i = 0; i < numPegs; ++i) {
		top = pegLookupTable[i];
		if (top >= 0) {
			// we search in both directions for valid moves
			for (t = i - 1; t >= 0; --t) {
				if (pegLookupTable[t] == -1 || top < pegLookupTable[t]) {
					HanoiBoardConfig lmove = board;
					lmove[top] = t;
					neighbors.push_back(lmove);
				}
			}
			for (t = i + 1; t < numPegs; ++t) {
				if (pegLookupTable[t] == -1 || top < pegLookupTable[t]) {
					HanoiBoardConfig rmove = board;
					rmove[top] = t;
					neighbors.push_back(rmove);
				}
			}
		}
	}
}

// a valid solution means every disk is on the last peg
bool HanoiPuzzle::isSolution(const HanoiBoardConfig& board) const {
	int endPegIndex = numPegs - 1;
	int i;
	for (i = 0; i < numDisks; ++i) {
		if (board[i] != endPegIndex) {
			return false;
		}
	}
	return true;
}

void HanoiPuzzle::display(const HanoiBoardConfig& board, std::stringstream& output, int step) const {
	if (board.size()) {
		unsigned int i;
		output << "Step " << step << ": ";
		for (i = 0; i < board.size(); ++i) {
			output << board[i] << " ";
		}
	} else {
		output << "Empty Hanoi Board.";
	}
}

const std::string& HanoiPuzzle::getName(void) const {
	return HANOI_PUZZLE_NAME;
}

