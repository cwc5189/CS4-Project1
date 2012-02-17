// File: $Id: jump.cpp,v 1.5 2012/02/13 04:27:11 p334-02e Exp p334-02e $
// Author:	 Jeff Lansing
//			 Chad Campbell
// Description:  n/a
// Revision History:
// 	$Log: jump.cpp,v $
// 	Revision 1.5  2012/02/13 04:27:11  p334-02e
// 	cleaned up
//
// 	Revision 1.4  2012/02/13 03:11:06  p334-02e
// 	Got file streams working and edited initialization value of file name strings
//
// 	Revision 1.3  2012/02/13 03:06:11  p334-02e
// 	Edited file stream checks and assignments
//
// 	Revision 1.2  2012/02/13 02:57:04  p334-02e
// 	Initial revision, added RCS tags
//
//
//

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <climits>
#include "Puzzle.h"
#include "PegPuzzle.h"

int main(int argc, char *argv[]) {
	const int NUM_JUMP_ARGS = 3;
	const char * STD_IO_BEHAVOIR = "-";
	if (argc == NUM_JUMP_ARGS) {
		std::string fileInName, fileOutName;
		std::ostream *os;
		std::istream *is;
		// only used with non standard output
		std::ifstream ifs; 
		std::ofstream ofs;  
		fileInName = argv[1];
		fileOutName = argv[2];
		// parse the input type
		if (fileInName == STD_IO_BEHAVOIR) {
			is = &std::cin;
		} else {
			ifs.open(fileInName.c_str());
			if (ifs.fail()) {
				std::cerr << "Invalid input file: " << fileInName << std::endl;
				return 2;
			}
			is = &ifs;
		}
		// parse the output type
		if (fileOutName == STD_IO_BEHAVOIR) {
			os = &std::cout;
		} else {
			ofs.open(fileOutName.c_str());
			if (ofs.fail()) {
				std::cerr << "Invalid output file: " << fileOutName << std::endl;
				return 2;
			}
			os = &ofs;
		}
		// solve the puzzle
		PegPuzzle pp = PegPuzzle();
		if (pp.parseInput(*is)) {
			pp.solve(*os);
		} else {
			return 2;
		}
	} else {
		std::cerr << "Invalid arguments.  Usage is jump [input] [output]" << std::endl;
		return 1;
	}

	return 0;
}
