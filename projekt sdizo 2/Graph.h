#include <iostream>
#include <sstream>
#include <fstream>
#pragma once
#include <vector>
#include <list>
#include <random>

using namespace std;

class AdjacencyListElement {
public:
	int weightOfEdge;
	int destinationVertex;
};

class Graph {
public:
	vector<vector<float>> weightMatrix;
	vector<list<AdjacencyListElement>> adjacencyList;
	int graphEdges, graphVertices, graphStart, graphEnd, edgeWeight;
	float infinity = numeric_limits<float>::infinity();
	bool minusWeight = false;

	void addElementToGraph(int initialVertex, int endVertex, int weightOfVertex, bool isDirected);
	void makeGraph();
	void removeGraph();
	bool fileReadGraph(string fileName, bool isDirected);
	void showWeightMatrix();
	void showAdjacencyList();

	void primsAlgorithmForMatrix(bool isItTests);
	void primsAlgorithmForList(bool isItTests);
	void dijkstraAlgorithmForMatrix(bool isItTests);
	void dijkstraAlgorithmForList(bool isItTests);
	void showResult(vector<float> distance, vector<int> previousVertices);

	void makeGraphForTestsWithDensity(int howMuchVertices, int whatDensity, bool isDirected);
};