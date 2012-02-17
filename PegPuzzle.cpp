//File: $Id: PegPuzzle.cpp,v 1.4 2012/02/14 16:55:46 p334-02e Exp p334-02e $
// Author:	 Jeff Lansing
//			 Chad Campbell
// Description:  n/a
// Revision History:
// 	$Log: PegPuzzle.cpp,v $
// 	Revision 1.4  2012/02/14 16:55:46  p334-02e
// 	removed unused functions and increased clarity
//
// 	Revision 1.3  2012/02/13 04:26:41  p334-02e
// 	Properly implemented isSolution() and display()
//
// 	Revision 1.2  2012/02/13 02:57:04  p334-02e
// 	Initial revision, added RCS tags
//
//
//

#include "PegPuzzle.h"
#include <iostream>

const std::string PegPuzzle::PEG_PUZZLE_NAME = "Peg Puzzle";

PegPuzzle::PegPuzzle() : numRows(-1), numCols(-1), horiz(false), vert(false), rdiag(false), ldiag(false) {	
	
}

PegPuzzle::~PegPuzzle(void) {

}

std::istream& PegPuzzle::parseInput(std::istream& is) {
	// get dimensions
	is >> numCols;
	is >> numRows;
	// get directions
	std::string directions;
	is >> directions;
	ldiag = (directions.find(LEFT_DIAGONAL_JUMP) != std::string::npos);
	rdiag = (directions.find(RIGHT_DIAGONAL_JUMP) != std::string::npos);
	vert = (directions.find(VERTICAL_JUMP) != std::string::npos);
	horiz = (directions.find(HORIZONTAL_JUMP) != std::string::npos);
	// fill board
	for(int r = 0; r < numRows; r++) {
		is.ignore();
		start.push_back(std::vector<char>());
		for(int c = 0; c < numCols; c++){
			start.at(r).push_back(is.get());
		}
	}
	return is;
}

const PegBoardConfig& PegPuzzle::getStart() const {
	return start;
}

void PegPuzzle::processMove(const PegBoardConfig& board, std::vector< PegBoardConfig >& neighbors, int x, int y, int dx, int dy, bool first) const {
	int destx = x + dx * 2;
	int desty = y + dy * 2;
	if (destx >= 0 && destx < numCols && desty >= 0 && desty < numRows) {
		int jumpedx = x + dx * 1;
		int jumpedy = y + dy * 1;
		char jumpedSpace = board.at(jumpedy).at(jumpedx);
		char destSpace = board.at(desty).at(destx);
		if (jumpedSpace == PEG_SPACE && destSpace == EMPTY_SPACE) {
			PegBoardConfig nconfig = board;
			nconfig.at(desty).at(destx) = PEG_SPACE;
			nconfig.at(jumpedy).at(jumpedx) = EMPTY_SPACE;
			nconfig.at(y).at(x) = EMPTY_SPACE;
			if (horiz) {
				processMove(nconfig, neighbors, destx, desty, -1, 0, false);
				processMove(nconfig, neighbors, destx, desty, 1, 0, false);
			}
			if (vert) {
				processMove(nconfig, neighbors, destx, desty, 0, -1, false);
				processMove(nconfig, neighbors, destx, desty, 0, 1, false);
			}
			if (ldiag) {
				processMove(nconfig, neighbors, destx, desty, -1, -1, false);
				processMove(nconfig, neighbors, destx, desty, 1, 1, false);
			}
			if (rdiag) {
				processMove(nconfig, neighbors, destx, desty, 1, -1, false);
				processMove(nconfig, neighbors, destx, desty, -1, 1, false);
			}
		}
	}
	if (!first) {
		neighbors.push_back(board);
	}
}

void PegPuzzle::getNeighbors(const PegBoardConfig& board, std::vector<PegBoardConfig>& neighbors) const {
	for(int y = 0; y < numRows; y++) {
		for(int x = 0; x < numCols; x++) {
			// for performance reasons, this check speeds it up considerably
			if (board.at(y).at(x) == PEG_SPACE) { 
				if (horiz) {
					processMove(board, neighbors, x, y, -1, 0, true);
					processMove(board, neighbors, x, y, 1, 0, true);
				}
				if (vert) {
					processMove(board, neighbors, x, y, 0, -1, true);
					processMove(board, neighbors, x, y, 0, 1, true);
				}
				if (ldiag) {
					processMove(board, neighbors, x, y, -1, -1, true);
					processMove(board, neighbors, x, y, 1, 1, true);
				}
				if (rdiag) {
					processMove(board, neighbors, x, y, 1, -1, true);
					processMove(board, neighbors, x, y, -1, 1, true);
				}
			}
		}
	}
}

bool PegPuzzle::isSolution(const PegBoardConfig& board) const {
	int numPegs = 0;
	for(int i = 0; i < numRows; i++) {
		for(int j = 0; j < numCols; j++) {
			if(board.at(i).at(j) == PEG_SPACE) {
				numPegs++;
				if (numPegs > 1) return false;
			}
		}
	}
	return (numPegs == 1);
}

void PegPuzzle::display(const PegBoardConfig& board, std::stringstream& output, int step) const {
	output << "Step " << step << ":\n";
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			output <<  board.at(i).at(j);
		}
		output << "\n";
	}
}

const std::string& PegPuzzle::getName(void) const{
	return PEG_PUZZLE_NAME;
}

