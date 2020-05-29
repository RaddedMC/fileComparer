# fileComparer
A command-line program to compare files, delete duplicates, and swap files. Useful for managing a large database.

Every file in the RaddedMC folder is reusable in other projects, need a quick way to set up a friendly error throwing function? Check out RaddedMC/throwErr. Need to have colours in output? Check out RaddedMC/colors!

Am I getting off topic? Okay...

fileComparer is a file comparing program, hence the name. It is nowhere near as powerful as diff, and is NOT a substitute for it. It is instead a simple comparison program that can tell if a file is an exact duplicate, or will tell you how many characters differ in the file, checking for things like simple 1 character typos.

Installation is simple. Clone the repo and run the justcompile.sh script (install gcc if you haven't already!!). Copy the executable into your /bin or just run it directly with ./. This program should run in Windows with little to no changes but is made for Linux.

Usage:
- fileComparer [FILE1] [OTHER FILES / *]
 - Checks differences and prints them
- fileComparer -s / --swap [FILE1] [FILE2]
  - Swaps files
- fileComparer -dd / --delete-dups [FILE1] [OTHER FILES / *]
  - Checks differences, if any, delete!
- fileComparer -h / --help
  - Prints help
- fileComparer -v / --verbose
  - With any valid function, will print verbose output
