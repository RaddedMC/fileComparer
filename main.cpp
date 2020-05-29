// RaddedMC's File Comparer! main

#include <iostream>
#include <string.h>
#include <string>
#include <cstdio>

using namespace std;

#define main_ver 1

#include "RaddedMC/throwErr/throwErr.h"
#include "RaddedMC/printHelp/printHelp.h"
#include "RaddedMC/colors/colors.h"
#include "RaddedMC/ifVerbose/printIfVerbose.h"
#include "RaddedMC/printLine/printLine.h"
#include "fileMgr.h"
#include "fileComparer.h"

// Features:
// - Compares two files to each other
// - Swap the two files with each other (useful for changing over to backups in Linux)
//   - Just renaming
// - Can delete duplicates

// Layout:
// - fileComparer [FILE1] [OTHER FILES]
//   - Checks differences and prints them
// - fileComparer -s / --swap [FILE1] [FILE2]
//   - Swaps files
// - fileComparer -d / --delete-dups [FILE1] [OTHER FILES]
//   - Checks differences, if any, delete!
// - fileComparer -h / --help
//   - Prints help
// - fileComparer -v / --verbose
//   - With any valid function, will print verbose output

// Modules:
// - File reader (returns file location or throws error)
// - File comparer (compares files, returns differences)
// - Main
// - throwErr
// - printIfVerbose (global variable ISVERBOSE set by main)
// - printHelp (I'm too lazy to code that for each app I make)

bool ISVERBOSE = false;

int * findDups(int argToC, char * argv[], int argc) {
	int * diffCounts = new int[argc-argToC-2];
	for (int targArg = argToC+1, count = 0; targArg != argc; targArg++, count++) {
		int differences = 0;
		if (strncmp(argv[argToC], argv[targArg], strlen(argv[argToC])) == 0) {
			// This way if you were to input the same file path twice, say while using *, it would skip.
			count--;
			continue;
		}
		try {
			differences = compareFiles(readFile(argv[argToC]), readFile(argv[targArg]));
		} catch (int e) {
			cerr << RED << "There was an error with one of your files. Code " << e << RESET << endl;
			printLine();
			continue;
		}
		// TODO: IF PATHS ARE SAME THEN DON'T COMPARE
		if (differences == 0) {
			cout << CYAN << argv[argToC] << RESET << " is a " << GREEN << "duplicate" << RESET << " of " << CYAN << argv[targArg] << endl << RESET;
		} else {
			cout << "There are " << RED << differences << " differences" << RESET << " between " << CYAN << argv[argToC] << RESET << " and " << CYAN << argv[targArg] << RESET << endl;
		}
		if (!ISVERBOSE) {
			cout << "Use --verbose for more details." << endl;
		}
		printLine();
		diffCounts[count] = differences;
	}
	diffCounts[argc-argToC-2] = -1;
	return diffCounts;
}

string toLower(string s) {
	// Apparently there is no .toLower class function for std::strings... somewhat dissapointing :D
	for (int i = 0; i != s.length(); i++) {
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] += 32;
	}
	return s;
}

int main(int argc, char * argv[])  {
	int argToC = 1;

	if (argc == 1) {
		throwErr("No command specified! Use --help for help.");
	}

	if (strncmp(argv[argToC], "-h", 2) == 0 || strncmp(argv[argToC], "--help", 5) == 0) {
		// -h
		printHelp(main_ver, "File Comparer");
	}

	// -v
	if (strncmp(argv[argToC], "-v", 3) == 0 || strncmp(argv[argToC], "--verbose", 9) == 0) {
		ISVERBOSE = true;
		argToC++;
		cout << "Verbose mode enabled!" << endl;
	}	
	printLine();

	if (argc < argToC+2) {
		// Not enough arguments!
		throwErr("Not enough arguments! Use --help for help.");
	}

	// -s
	if (strncmp(argv[argToC], "-s", 3) == 0 || strncmp(argv[argToC], "--swap", 6) == 0) {
		argToC++;
		if (argc < argToC+2) {
			throwErr("Not enough arguments! Use --help for help.");
		}
		if (argc > argToC+2) {
			throwErr("Too many arguments! Use --help for help.");
		}
		if (strncmp(argv[argToC], argv[argToC+1], strlen(argv[argToC])) == 0) {
			// This way if you were to input the same file path twice, say while using *, it would skip.
			throwErr("You've inputted the same file twice! Use --help for help.");
		}

		findDups(argToC, argv, argc);

		cout << "Swapping " << argv[argToC] << " and " << argv[argToC+1] << "..." << endl;
		string nevold = argv[argToC]; // Avoiding the new keyword the big brain way
		string oldnev = argv[argToC+1];
		int lastSlash = 0;
		for (int i = 0; i != nevold.length(); i++) {
			if (nevold[i] == '/' && nevold[i+1] != 0) { // Because putting a slash after a file in cli does things
				lastSlash = i;
			}
		}
		string tempN = nevold.erase(lastSlash) + "/tempf";
		nevold = argv[argToC];

		if (rename(nevold.c_str(), tempN.c_str()) != 0) {
			throwErr("Error renaming " + nevold + " to " + tempN, 4);
		}
		if (rename(oldnev.c_str(), nevold.c_str()) != 0) {
			throwErr("Error renaming " + oldnev + " to " + nevold, 4);
		}
		if (rename(tempN.c_str(), oldnev.c_str()) != 0) {
			throwErr("Error renaming " + tempN + " to " + oldnev, 4);
		}
		// Turn file1 to tempN
		// Turn file2 to file1
		// Turn tempN to file2
		cout << "Files swapped successfully!" << endl;
		return 0;
	}

	// -d
	if (strncmp(argv[argToC], "-d", 3) == 0 || strncmp(argv[argToC], "--delete-dups", 7) == 0) { // Want to make sure the user enters delete, that way we can be sure they want to do that
		argToC++;
		// Find duplicates
		int * differences = findDups(argToC, argv, argc);

		// Select them
			// For every item in differences, if the difference is greater than zero, add it's corresponding argv to a list
		int targetCount = 0;
		for (int i = 0; *(differences+i) != -1; i++) { // I know two identical loops is not efficient, I still
													   // can't figure out dynamic allocation :D
			if (*(differences+i) == 0) {
				targetCount++;
			}
		}
		if (targetCount == 0) {
			cout << GREEN << "No duplicates found! Exiting..." << RESET << endl;
			exit(0);
		}
		string * targets = new string[targetCount];
		for (int i = 0, target = 0; *(differences + i) != -1; i++) {
			if (*(differences+i) == 0) {
				targets[target] = argv[argToC+i+2];
				target++;
			}
		}

		cout << "To delete:" << endl;
		// Show list of files to delete to user
		for (int i = 0; i != targetCount; i++) {
			cout << YELLOW << "\t" << targets[i] << RESET << endl;
		}
		// Ask for confirmation
		cout << "Delete these files? [y/N] ";
		string input;
		cin >> input;
		if (strncmp(toLower(input).c_str(), "y", 1) == 0) {
			// Delete!
			for (int i = 0; i != targetCount; i++) {
				if (remove(targets[i].c_str()) != 0) {
					cerr << RED << "Error deleting " << targets[i] << "." << endl;
				} else {
					printIfVerbose(GREEN + targets[i] + " deleted successfully!\n" + RESET);
				}
			}
		}
		return 0;
	}

	int * differences = findDups(argToC, argv, argc);
}