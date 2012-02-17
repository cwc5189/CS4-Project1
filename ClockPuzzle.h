// File: $Id: ClockPuzzle.h,v 1.2 2012/01/29 01:48:11 jrl6166 Exp jrl6166 $
// Author:	 Jeff Lansing
// Description:  n/a
// Revision History:
// 	$Log: ClockPuzzle.h,v $
// 	Revision 1.2  2012/01/29 01:48:11  jrl6166
// 	added documentation
//
// 	Revision 1.1  2012/01/27 00:34:47  jrl6166
// 	Initial revision
//
// 	Revision 1.2  2012/01/24 15:01:50  jrl6166
// 	initial clock puzzle file
//
//

#ifndef _CLOCK_PUZZLE_H_
#define _CLOCK_PUZZLE_H_

#include "Puzzle.h"
#include <vector>
#include <string>

/// Config type used by our Clock Board
typedef int ClockBoardConfig;

/// Clock specific puzzle
/// @author Jeff Lansing 
class ClockPuzzle : public Puzzle <ClockBoardConfig> {
public:
	/// Constructs a clock puzzle with the given properties
	/// @param numHours hours on the clock
	/// @param timeStart start time on the clock
	/// @param timeEnd end time to set it to
	ClockPuzzle(int numHours, int timeStart, int timeEnd);
	
	/// Destructor
	~ClockPuzzle(void);

	/// Gets the start clock config (start time)
	/// @return init board config
	virtual const ClockBoardConfig& getStart() const;
	
	/// Gets the neighbors of the given clock time
	/// @param board current time
	/// @param empty list to be populated with next valid times
	virtual void getNeighbors(const ClockBoardConfig& board, std::vector<ClockBoardConfig>& neighbors) const;
	
	/// Determines if the given clock's time is the end time
	/// @param board icurrent time
	/// @return true if the end time, false otherwise
	virtual bool isSolution(const ClockBoardConfig& board) const;
	
	/// Displays the given clock time
	/// @param board the current clock time
	/// @param output the ostream to log to
	/// @param step the step counter
	virtual void display(const ClockBoardConfig& board, std::stringstream& output, int step) const;
	
	/// Gets the clock puzzle's name
	/// @return reference to the clock puzzle's name
	virtual const std::string& getName(void) const;
private:
	static const std::string CLOCK_PUZZLE_NAME;
	int numHours, timeStart, timeEnd;
};

#endif
