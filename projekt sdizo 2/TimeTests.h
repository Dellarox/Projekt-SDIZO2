#pragma once
#include <iomanip>
#include <windows.h>
#include "Graph.h"

using namespace std;

class TimeTests {
public:
	double timeOfTest = 0;

	void timeTestsForPrimsAlgorithmOnMatrix(Graph g, int howMuchVertices, int whatDensity);
	void timeTestsForPrimsAlgorithmOnList(Graph g, int howMuchVertices, int whatDensity);

	void timeTestsForDijsktraAlgorithmOnMatrix(Graph g, int howMuchVertices, int whatDensity);
	void timeTestsForDijsktraAlgorithmOnList(Graph g, int howMuchVertices, int whatDensity);
};