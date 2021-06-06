#include "TimeTests.h"

long long int read_QPC() {
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}

void TimeTests::timeTestsForPrimsAlgorithmOnMatrix(Graph g, int howMuchVertices, int whatDensity) {
	srand(time(NULL));
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	
	timeOfTest = 0;

	for (int i = 0; i < 100; i++) {
		g.makeGraphForTestsWithDensity(howMuchVertices, whatDensity, false);
		start = read_QPC();

		g.primsAlgorithmForMatrix(true);

		elapsed = read_QPC() - start;

		timeOfTest = timeOfTest + (1000000.0 * elapsed) / frequency;
	}
	timeOfTest = timeOfTest / 100;
	cout << "Gêstoœæ grafu: " << whatDensity << "; iloœæ wierzcho³ków: " << howMuchVertices << "; œredni czas wykonania algorytmu Prima dla macierzy w us: " << timeOfTest << "." << endl;
}

void TimeTests::timeTestsForPrimsAlgorithmOnList(Graph g, int howMuchVertices, int whatDensity) {
	srand(time(NULL));
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	timeOfTest = 0;

	for (int i = 0; i < 100; i++) {
		g.makeGraphForTestsWithDensity(howMuchVertices, whatDensity, false);
		start = read_QPC();

		g.primsAlgorithmForList(true);

		elapsed = read_QPC() - start;

		timeOfTest = timeOfTest + (1000000.0 * elapsed) / frequency;
	}
	timeOfTest = timeOfTest / 100;
	cout << "Gêstoœæ grafu: " << whatDensity << "; iloœæ wierzcho³ków: " << howMuchVertices << "; œredni czas wykonania algorytmu Prima dla listy w us: " << timeOfTest << "." << endl;
}

void TimeTests::timeTestsForDijsktraAlgorithmOnMatrix(Graph g, int howMuchVertices, int whatDensity) {
	srand(time(NULL));
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	timeOfTest = 0;

	for (int i = 0; i < 100; i++) {
		g.makeGraphForTestsWithDensity(howMuchVertices, whatDensity, true);
		start = read_QPC();

		g.dijkstraAlgorithmForMatrix(true);

		elapsed = read_QPC() - start;

		timeOfTest = timeOfTest + (1000000.0 * elapsed) / frequency;
	}
	timeOfTest = timeOfTest / 100;
	cout << "Gêstoœæ grafu: " << whatDensity << "; iloœæ wierzcho³ków: " << howMuchVertices << "; œredni czas wykonania algorytmu Dijkstry dla macierzy w us: " << timeOfTest << "." << endl;
}

void TimeTests::timeTestsForDijsktraAlgorithmOnList(Graph g, int howMuchVertices, int whatDensity) {
	srand(time(NULL));
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	timeOfTest = 0;

	for (int i = 0; i < 100; i++) {
		g.makeGraphForTestsWithDensity(howMuchVertices, whatDensity, true);
		start = read_QPC();

		g.dijkstraAlgorithmForList(true);

		elapsed = read_QPC() - start;

		timeOfTest = timeOfTest + (1000000.0 * elapsed) / frequency;
	}
	timeOfTest = timeOfTest / 100;
	cout << "Gêstoœæ grafu: " << whatDensity << "; iloœæ wierzcho³ków: " << howMuchVertices << "; œredni czas wykonania algorytmu Dijkstry dla listy w us: " << timeOfTest << "." << endl;
}
