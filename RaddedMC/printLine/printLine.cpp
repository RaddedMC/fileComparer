// Terminal size from https://stackoverflow.com/questions/23369503/get-size-of-terminal-window-rows-columns

#include <iostream>
#include <sys/ioctl.h> //ioctl() and TIOCGWINSZ
#include <unistd.h> // for STDOUT_FILENO
using namespace std;

void printLine(int dash = 0) {
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	for (int j = 0; j != w.ws_col; j++) {
		if (dash == 0 || j % dash == 0) {
			cout << '-';
		} else {
			cout << ' ';
		}
	}
	cout << endl;
}

string genLine(int dash = 0) {
	struct winsize w;
	string line = "";
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	for (int j = 0; j != w.ws_col; j++) {
		if (dash == 0 || j % dash == 0) {
			line += '-';
		} else {
			line += ' ';
		}
	}
	line += "\n";
	return line;
}

int getWindowW() {
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return w.ws_col;
}

int getWindowH() {
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return w.ws_col;
}