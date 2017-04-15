test: test.o TofeGame.o TofeHeuristicEmptyFactory.o TofeHeuristicDiffFactory.o TofeHeuristicReverseFactory.o TofeHeuristicDiff.o TofeHeuristicReverse.o SgHashTable.o
	g++ -o test test.o TofeGame.o TofeHeuristicEmptyFactory.o TofeHeuristicDiffFactory.o TofeHeuristicReverseFactory.o TofeHeuristicDiff.o TofeHeuristicReverse.o SgHashTable.o -std=C++11
	mv test ./DoTest/TestHashStat

SgHashTable.o: SgHashTable.cpp
	g++ -c SgHashTable.cpp -std=c++11

test.o: test.cpp
	g++ -c test.cpp -std=c++11 -DTEST -DSTAT

TofeHeuristicEmptyFactory.o: ./TofeGame/TofeHeuristic/TofeHeuristicEmpty/TofeHeuristicEmptyFactory.cpp
	g++ -c ./TofeGame/TofeHeuristic/TofeHeuristicEmpty/TofeHeuristicEmptyFactory.cpp -std=c++11

TofeHeuristicDiffFactory.o: ./TofeGame/TofeHeuristic/TofeHeuristicDiff/TofeHeuristicDiffFactory.cpp
	g++ -c ./TofeGame/TofeHeuristic/TofeHeuristicDiff/TofeHeuristicDiffFactory.cpp -std=c++11

TofeHeuristicReverseFactory.o: ./TofeGame/TofeHeuristic/TofeHeuristicReverse/TofeHeuristicReverseFactory.cpp
	g++ -c ./TofeGame/TofeHeuristic/TofeHeuristicReverse/TofeHeuristicReverseFactory.cpp -std=c++11

TofeHeuristicDiff.o: ./TofeGame/TofeHeuristic/TofeHeuristicDiff/TofeHeuristicDiff.cpp
	g++ -c ./TofeGame/TofeHeuristic/TofeHeuristicDiff/TofeHeuristicDiff.cpp -std=c++11

TofeHeuristicReverse.o: ./TofeGame/TofeHeuristic/TofeHeuristicReverse/TofeHeuristicReverse.cpp
	g++ -c ./TofeGame/TofeHeuristic/TofeHeuristicReverse/TofeHeuristicReverse.cpp -std=c++11

TofeGame.o: ./TofeGame/TofeGame.cpp
	g++ -c ./TofeGame/TofeGame.cpp -std=c++11

clean:
	rm test.o TofeGame.o TofeHeuristicEmptyFactory.o TofeHeuristicDiffFactory.o TofeHeuristicReverseFactory.o TofeHeuristicDiff.o TofeHeuristicReverse.o SgHashTable.o
