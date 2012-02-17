// File: 	$Id: Puzzle.h,v 1.3 2012/01/29 01:24:38 jrl6166 Exp jrl6166 $
// Author:	Jeff Lansing
// Description:
//		Abstract type for all puzzles
// Revisions:
//		$Log: Puzzle.h,v $
//		Revision 1.3  2012/01/29 01:24:38  jrl6166
//		Added doxygen comments, improved solve method
//
//		Revision 1.2  2012/01/27 00:37:36  jrl6166
//		new template friendly interface
//
//

#ifndef _PUZZLE_H_
#define _PUZZLE_H_

#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <map>

/// Templated base puzzle with generic non-virtual solver
/// @author Jeff Lansing
template <typename BoardConfig>
class Puzzle {
public:
	/// For safety if derived puzzles make use of dynamic memory
	virtual ~Puzzle() { }
	
	/// Solves the puzzle in a generic way, logs output with the given ostream
	/// @param os the ostream used to log output from solving
	void solve(std::ostream& os) const;
	
	/// Gets the starting board configuration
	/// @return a reference to the init puzzle board config
	virtual const BoardConfig& getStart() const = 0;
	
	/// Gets the neighbors from the given board.  Our concept of neighbors is often best 
	/// understood as every possible next move that could be exceuted given the passed in board.
	/// @param board the current board config
	/// @param neighbors empty container to be populated with all valid next moves
	virtual void getNeighbors(const BoardConfig& board, std::vector<BoardConfig>& neighbors) const = 0;
	
	/// Determines if the board is a final solution
	/// @return if board config is a solution
	virtual bool isSolution(const BoardConfig& board) const = 0;
	
	/// Outputs specialized information of the given board
	/// @param board the current board config
	/// @param output the ostream to log to
	/// @param step the step counter
	virtual void display(const BoardConfig& board, std::stringstream& output, int step) const = 0;
	
	/// Gets the puzzle's name
	/// @return reference to the puzzle's name
	virtual const std::string& getName(void) const = 0;
};

/// Templated functions must be defined in the header file so we're doing that here
/// This is the core of the solver, templated to work with various types and every kind of puzzle
template <typename BoardConfig>
void Puzzle<BoardConfig>::solve(std::ostream& os) const {	
	std::queue<BoardConfig> boardQueue; // bfs queue
	BoardConfig start = getStart();	// start config
	std::stringstream strm; // used for ostream output
	std::map<BoardConfig, BoardConfig> visited; // to mark as visited
	BoardConfig curBoard;	// temporary
	std::vector<BoardConfig> curMoves; // for neighbors
	std::vector<BoardConfig> moves; // for paths
	std::vector<BoardConfig> readOut; // for logging all the moves at the end
	size_t i;
	int step = 0;
	
	// enqueue and mark start as visited
	boardQueue.push(start);
	visited[start] = start;
    
	// iterate while the queue isn't empty and 
	// the puzzle is not solved
	while (boardQueue.size()) {
		curBoard = boardQueue.front();
		if (isSolution(curBoard)) {
			moves.push_back(curBoard);
			break;
		}
		boardQueue.pop();
		// get the next moves from the board
		curMoves.resize(0);
		getNeighbors(curBoard, curMoves);
		// process the new moves for a solution
		for (i = 0; i < curMoves.size(); ++i) {
			if ((visited.insert(std::pair<BoardConfig, BoardConfig>(curMoves[i], curBoard))).second) {
				boardQueue.push(curMoves[i]);
			}
		}
	}
	
	// if the queue is not empty there is a solution
	if (boardQueue.size()) {
		os << "Board Solution Found For " << getName() << "!\n";
		display(start, strm, step);
		strm << "\n"; 
		// reconstructs the list backwards
		// from the visited table
		for (i = 0; i < moves.size(); ++i) {
			while (moves[i] != start) {
				readOut.push_back(moves[i]);
				moves[i] = visited[moves[i]];
			}
		}
		// uint safe way to iterate backwards
		for (i = readOut.size(), step = 1; i-- > 0; ++step) {
			display(readOut[i], strm, step);
			strm << "\n";
		}
		os << strm.str();
	} else {
		os << "No Board Solution Found For " << getName() << "!\n";
	}
}

#endif
