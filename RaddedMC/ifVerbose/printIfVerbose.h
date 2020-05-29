// RaddedMC printIfVerbose

#include <iostream>

extern bool ISVERBOSE;
template <typename T> //https://stackoverflow.com/questions/28096863/accept-all-types-as-argument-in-function
// Yay now this thing can take all types!
void printIfVerbose(T const & toPrint) {
	if (ISVERBOSE) {
		std::cout << toPrint;
	}
}