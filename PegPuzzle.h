// File: $Id: PegPuzzle.h,v 1.3 2012/02/13 04:52:45 p334-02e Exp $
// Author:	 Jeff Lansing
//			 Chad Campbell
// Description:  n/a
// Revision History:
// 	$Log: PegPuzzle.h,v $
// 	Revision 1.3  2012/02/13 04:52:45  p334-02e
// 	Fixed vector typedef, was missing spaces
//
// 	Revision 1.2  2012/02/13 02:57:04  p334-02e
// 	Initial revision, added RCS tags
//
//
//
#ifndef _PEG_PUZZLE_H_
#define _PEG_PUZZLE_H_

#include "Puzzle.h"
#include <vector>
#include <string>

/// Config type used by our Peg Board
typedef std::vector< std::vector<char> > PegBoardConfig;

/// Peg specific puzzle
/// @author Chad Campbell
/// @author Jeff Lansing
class PegPuzzle :  public Puzzle <PegBoardConfig> {
public:
	/// Constructs a puzzle
	PegPuzzle();

	/// Destructor
	~PegPuzzle(void);
	
	/// Keeps IO out of the constructor, where it is difficult to 
	/// recover if things fail
	/// @param in input stream
	std::istream& parseInput(std::istream& in);
	
	/// Gets the starting peg board config
	/// @return peg board config vector
	virtual const PegBoardConfig& getStart() const;

	/// Gets all possible moves stemming from the given board
	/// @param board current puzzle state
	/// @param empty list to be populated with next valid moves
	virtual void getNeighbors(const PegBoardConfig& board, std::vector< PegBoardConfig >& neighbors) const;

	/// Checks if the puzzle has been solved
	/// @return true if solved, false if not
	virtual bool isSolution(const PegBoardConfig& board) const;

	/// Displays the given peg board
	/// @param board the current peg board config
	/// @param output the ostream to log to
	/// @param step the step counter
	virtual void display(const PegBoardConfig& board, std::stringstream& output, int step) const;

	/// Gets the peg puzzle's name
	/// @return the peg puzzle's name
	virtual const std::string& getName(void) const;

	static const char PEG_SPACE = '+';
	static const char EMPTY_SPACE = '.';
	static const char OUT_OF_BOUNDS_SPACE = '#';
	static const char HORIZONTAL_JUMP = '-';
	static const char VERTICAL_JUMP = '|';
	static const char RIGHT_DIAGONAL_JUMP = '/';
	static const char LEFT_DIAGONAL_JUMP = '\\';
private:
	/// Recursive move making function, works in any direction with step parameters
	/// @param board current board config
	/// @param neighbors moves vector
	/// @param x the column
	/// @param y the row
	/// @param dx the step in columns
	/// @param dy the step in rows
	/// @param first if the first move
	void processMove(const PegBoardConfig& board, std::vector< PegBoardConfig >& neighbors, int x, int y, int dx, int dy, bool first) const;
	
	static const std::string PEG_PUZZLE_NAME;
	
	PegBoardConfig start; // start board
	int numRows, numCols; // dimensions of the board
	bool vert, horiz, ldiag, rdiag; // cached valid search directions
};

#endif
