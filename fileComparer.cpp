//RaddedMC's File Comparer! fileComparer.cpp

#include <string>
#include <string.h>
#include "fileComparer.h"
#include "RaddedMC/ifVerbose/printIfVerbose.h"
#include "RaddedMC/colors/colors.h"
#include "RaddedMC/printLine/printLine.h"

using namespace std;

int compareFiles(std::string file1, std::string file2) {
	int diffTally = 0;
	int shortestLen = file1.length();
	int file2Len = file2.length();
	printIfVerbose("File 1 is "); printIfVerbose(shortestLen); printIfVerbose(" characters long! ");
	printIfVerbose("File 2 is "); printIfVerbose(file2Len); printIfVerbose(" characters long!\n");
	// TODO: Delete file2Len if it is equal to shortestLen
	if (file2Len != shortestLen) {
		diffTally++; // If file lengths are not the same, add a difference
		printIfVerbose("Difference++! Lengths are not identical.\n");
	}

	if (file2Len < shortestLen) {
		shortestLen = file2Len;
	}

	// Read each character in files until end of shortest file

	for (int i = 0, offset = 0, oneSet = 0, twoSet = 0; file1[i+oneSet] != 0 && file2[i+twoSet] != 0; i++) {

		// Generate needed chars (https://stackoverflow.com/questions/8437099/c-convert-char-to-const-char)
		string sym1(1, file1[i+oneSet]);
		string sym2(1, file2[i+twoSet]);
		string sym2o(1, file2[i+twoSet-offset]);
		const char * f1c = sym1.c_str();
		const char * f2c = sym2.c_str();
		const char * f2co = sym2o.c_str();
		// f1c, f2c
		// f1c, f2co

		if (*f1c == '\n') {
			// Iterate through file2 until you pull a \n
			int j;
			for (j = 0; file2.at(i+twoSet+j) != '\n'; j++) {}
			// set twoSet to j value
			twoSet+=j;
			offset = 0;
			printIfVerbose("\nRead in a newline character... resetting bounds.\n");
			continue;
		}
		if (*f2c == '\n') {
			// Iterate through file1 until you pull a \n
			int j;
			for (j = 0; file1[i+oneSet+j] != '\n'; j++) {}
			// set twoSet to j value
			oneSet+=j;
			offset = 0;
			printIfVerbose("\nRead in a newline character... resetting bounds.\n");
			continue;
		}

		if ((strcmp(f1c, f2c) == 0) && offset != 0) {
			// Characters match without an offset, previous offender was probably a 1 char typo, clear offset.
			// GREEN
			offset = 0;
			printIfVerbose(GREEN); printIfVerbose(file1.at(i+oneSet)); printIfVerbose(" = "); printIfVerbose(file2.at(i+twoSet)); printIfVerbose(" | ");
			// TODO: get rid of this disgusting mess and implement a difference counter on the right side of the screen using getwindoww from printLine
		}
		if ((strcmp(f1c, f2c) == 0)) {
			// GREEN
			printIfVerbose(GREEN); printIfVerbose(file1.at(i+oneSet)); printIfVerbose(" = "); printIfVerbose(file2.at(i+twoSet)); printIfVerbose(" | ");
		}
		else if (strcmp(f1c, f2co) == 0) {
			// Offset characters match
			// YELLOW
			printIfVerbose(YELLOW); printIfVerbose(file1.at(i+oneSet)); printIfVerbose(" = "); printIfVerbose(file2.at(i+twoSet)); printIfVerbose(" | ");
		} else if (strcmp(f1c, f2co) != 0 && offset != 0) {
			// Offset characters don't match, and neither do originals because that was tested. Reset offset!
			// RED
		 	printIfVerbose("\nFound non-equal characters! Resetting offset...\n");
		 	printIfVerbose(RED);
		 	printIfVerbose("File 1 c"); printIfVerbose(i+oneSet); printIfVerbose(": "); printIfVerbose(file1.at(i+oneSet)); printIfVerbose(" is not equal to File 2 c"); printIfVerbose(i+twoSet-offset); printIfVerbose(": "); printIfVerbose(file2.at(i+twoSet-offset)); printIfVerbose(", "); printIfVerbose(file2.at(i+twoSet)); printIfVerbose("\n");
		 	printIfVerbose(RESET);
		 	diffTally++;
		 	offset = 0;
		} else {
			// Nothing matches, add offset
			// RED
			printIfVerbose("\nFound non-equal characters! Adding to offset...\n");
		 	printIfVerbose(RED);
		 	printIfVerbose("File 1 c"); printIfVerbose(i+oneSet); printIfVerbose(": "); printIfVerbose(file1.at(i+oneSet)); printIfVerbose(" is not equal to File 2 c"); printIfVerbose(i+twoSet-offset); printIfVerbose(": "); printIfVerbose(file2.at(i+twoSet-offset)); printIfVerbose("\n");
		 	printIfVerbose(RESET);
		 	diffTally++;
		 	offset++;
		}
		printIfVerbose(RESET);
	}
	printIfVerbose(genLine());

		// If a character is different, add to an offset
			// Difference should be marked as RED
		// Compare characters by position and by position-offset
			// If the characters are the same, GREEN
			// If the offsets are the same, YELLOW
			// If neither are the same, reset the offset and keep going, RED!
		// Only reds are added to counter

	return diffTally;
}
