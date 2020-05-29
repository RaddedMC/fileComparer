// RaddedMC's printHelp (he is lazy)

#include <iostream>
#include <string>
#include "../colors/colors.h"
void printHelp(const float ver = -1, const std::string programTitle = "") {
	if (!(ver == -1 || programTitle.empty())) {
		std::cout << BLUE << "RaddedMC's " << programTitle << RESET << " v" << ver << ":" << endl;
		std::cout << "This program can be a useful tool for managing config file backups or package manager databases." << endl;
		std::cout << 
	   "- fileComparer [FILE1] [OTHER FILES]\n - Checks differences and prints them\n- fileComparer -s / --swap [FILE1] [FILE2]\n  - Swaps files\n- fileComparer -dd / --delete-dups [FILE1] [OTHER FILES]\n  - Checks differences, if any, delete!\n- fileComparer -h / --help\n  - Prints help\n- fileComparer -v / --verbose\n  - With any valid function, will print verbose output";
	   std::cout << endl;
	}
	exit(0);
}