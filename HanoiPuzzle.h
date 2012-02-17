// File: $Id: HanoiPuzzle.h,v 1.2 2012/01/29 01:48:29 jrl6166 Exp jrl6166 $
// Author:	 Jeff Lansing
// Description:  n/a
// Revision History:
// 	$Log: HanoiPuzzle.h,v $
// 	Revision 1.2  2012/01/29 01:48:29  jrl6166
// 	added documentation
//
// 	Revision 1.1  2012/01/24 16:47:37  jrl6166
// 	Initial revision
//
//
#ifndef _HANOI_PUZZLE_H_
#define _HANOI_PUZZLE_H_

#include "Puzzle.h"
#include <vector>
#include <string>

/// Config type used by our Hanoi Board
typedef std::vector<int> HanoiBoardConfig;

/// Hanoi specific puzzle
/// @author Jeff Lansing
class HanoiPuzzle : public Puzzle <HanoiBoardConfig> {
public:
	/// Generates a hanoi puzzle with the given number of pegs and disks
	/// @param numPegs pegs for the hanoi config
	/// @param numDisks disks for the hanoi config
	HanoiPuzzle(int numPegs, int numDisks);
	
	/// Hanoi puzzle destructor	
	~HanoiPuzzle(void);

	/// Gets the start hanoi board config
	/// @return hanoi config vector
	const HanoiBoardConfig& getStart() const;
	
	/// Gets all possible next moves given the passed in board
	/// @param board current puzzle state
	/// @param empty list to be populated with next valid moves
	virtual void getNeighbors(const HanoiBoardConfig& board, std::vector< HanoiBoardConfig >& neighbors) const;
	
	/// Determines if the hanoi board is solved
	/// @return true if solved, false if not
	virtual bool isSolution(const HanoiBoardConfig& board) const;
	
	/// Displays the given hanoi board
	/// @param board the current hanoi board config
	/// @param output the ostream to log to
	/// @param step the step counter
	virtual void display(const HanoiBoardConfig& board, std::stringstream& output, int step) const;
	
	/// Gets the hanoi puzzle's name
	/// @return hanoi puzzle name
	const std::string& getName(void) const;
private:
	static const std::string HANOI_PUZZLE_NAME;
	HanoiBoardConfig start;
	int numPegs, numDisks;
	int *pegLookupTable;
};

#endif
