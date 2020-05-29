g++ main.cpp RaddedMC/throwErr/throwErr.cpp fileComparer.cpp fileMgr.cpp RaddedMC/printLine/printLine.cpp -o fileComparer
./fileComparer -v TestFiles/AllStar.txt TestFiles/NotAllStar.txt TestFiles/DefinitelyNotAllStar.txt
rm fileComparer
