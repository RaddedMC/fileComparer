//RaddedMC's File Comparer! fileMgr.cpp

// THIS FILE THROWS:
// 1 - unable to open
// 2 - unable to read
// 3 - won't actually throw anything but unable to close

#include <string>
#include <string.h> // strerror
#include "fileMgr.h"
#include <fstream>
#include <sstream>
#include "RaddedMC/ifVerbose/printIfVerbose.h"
#include "RaddedMC/printLine/printLine.h"
using namespace std;

string readFile(std::string location) {

	// Couldn't figure out how to read entire files so I reused my code from my clitodo project
	// Some help on https://stackoverflow.com/questions/13446593/c-ifstream-error-checking
	ifstream iFile(location);

	if (!iFile) {
		printIfVerbose("Fatal error: Unable to open file at " + location + ". Throwing error code 1.\n");
		throw 1;
		// unable to open file
	} else {
		printIfVerbose("File at " + location + " opened successfully!\n");
		string output;
		stringstream outputS;
		outputS << iFile.rdbuf();
		output = outputS.str();

		// Read successfully?
		char * err = strerror(errno);
		if (strncmp(err, "Success", 7) != 0) {
			printIfVerbose("Fatal error: Unable to read file at " + location + ". Throwing error code 2.\n");
			throw 2;
		}
		printIfVerbose("File at " + location + " read successfully!\n");

		iFile.close();

		// Closed successfully?
		err = strerror(errno);
		if (strncmp(err, "Success", 7) != 0) {
			printIfVerbose("Error: Unable to close file at " + location + ". Continuing execution...\n");
		} else {
			printIfVerbose("File at " + location + " closed successfully!\n");
		}
		printIfVerbose(genLine());
		return output;
	}
}