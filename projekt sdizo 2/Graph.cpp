#include "Graph.h"

bool fileReadLine(ifstream& file, int tab[], int size) {
	string s;
	getline(file, s);

	if (file.fail() || s.empty())
		return(false);

	istringstream in_ss(s);

	for (int i = 0; i < size; i++)
	{
		in_ss >> tab[i];
		if (in_ss.fail())
			return(false);
	}
	return(true);
}

void Graph::addElementToGraph(int initialVertex, int endVertex, int weightOfEdge, bool isDirected) {
	weightMatrix[initialVertex][endVertex] = weightOfEdge;

	AdjacencyListElement elementOfList;
	elementOfList.destinationVertex = endVertex;
	elementOfList.weightOfEdge = weightOfEdge;
	adjacencyList[initialVertex].push_back(elementOfList);

	if (!isDirected) {
		weightMatrix[endVertex][initialVertex] = weightOfEdge;

		elementOfList.destinationVertex = initialVertex;
		elementOfList.weightOfEdge = weightOfEdge;
		adjacencyList[endVertex].push_back(elementOfList);
	}
}

void Graph::makeGraph() {

}

void Graph::removeGraph(){
	weightMatrix.clear();
	weightMatrix.resize(0);

	for (int i = 0; i < adjacencyList.size(); i++) {
		adjacencyList[i].clear();
		adjacencyList[i].resize(0);
	}
	adjacencyList.clear();
	adjacencyList.resize(0);

	minusWeight = false;
}


bool Graph::fileReadGraph(string fileName, bool isDirected) {
	ifstream file;
	int tab[4];
	file.open(fileName.c_str());

	if (file.is_open())
	{
		if (fileReadLine(file, tab, 4))
		{
			removeGraph(); // czyszczenie pamieci z poprzedniego grafu

			graphEdges = tab[0]; // wlasciwosci nowego grafu
			graphVertices = tab[1];
			graphStart = tab[2];
			graphEnd = tab[3];

			weightMatrix.resize(graphVertices, vector<float>(graphVertices, infinity));
			adjacencyList.resize(graphVertices);

			for (int i = 0; i < graphEdges; i++)
				if (fileReadLine(file, tab, 3))
				{
					if (tab[2] < 0)
						minusWeight = true; // sprawdzam czy krawedz ma ujemna wage
					addElementToGraph(tab[0], tab[1], tab[2], isDirected);
				}
				else
				{
					cout << "File error - READ EDGE" << endl;
					break;
				}
			return true;
		}
		else
			cout << "File error - READ INFO" << endl;
		file.close();
		return false;
	}
	else
		cout << "File error - OPEN" << endl;
	
	return false;
}

void Graph::showWeightMatrix() {
	for (int i = 0; i < graphVertices; i++) {
		for (int j = 0; j < graphVertices; j++) {
			cout << weightMatrix[i][j] << "	 ";
		}
		cout << endl;
	}
	cout << endl;
}

void Graph::showAdjacencyList() {
	cout << "Numer wierzcho³ka -> wierzcho³ek docelowy | waga œcie¿ki" << endl;
	for (int i = 0; i < graphVertices; i++) {
		cout << i;
		for (AdjacencyListElement element : adjacencyList[i]) {
			cout << " -> " << element.destinationVertex << " | " << element.weightOfEdge;
		}
		cout << endl;
	}
	cout << endl;
}

//algorytmy

void Graph::primsAlgorithmForMatrix(bool isItTests) {
	vector<int> visitedVertices; // tworzê tablicê, w której bêd¹ przechowywane odwiedzone wierzcho³ki
	int firstVertex = graphStart; // ustalam pierwszy wierzcho³ek (bêdzie on równie¿ odpowiada³ za wierzcho³ek, w którym aktualnie siê znajdujemy)
	visitedVertices.push_back(firstVertex); // i wrzucam go do odwiedzonych wierzcho³ków
	int nextVertex; // wierzcho³ek, który bêdzie odwiedzamy jako kolejny
	int mst = 0; // tutaj bêdzie przechowywane mst

	for (int i = 0; i < graphVertices - 1; i++) { // przegl¹dam graphVertices-1 wierzcho³ków, poniewa¿ jeden ju¿ wrzucony do visitedVertices
		float minimumFoundedValue = infinity; // t¹ zmienn¹ bêdziemy szukaæ najmniejszej wartoœci dlatego na pocz¹tku jest ustawiona na nieskoñczonoœæ

		for (int j = 0; j < (int) visitedVertices.size(); j++) { // przechodzê po odwiedzonych wierzcho³kach
			for (int n = 0; n < graphVertices; n++) { // przechodzê po wszystkich, równie¿ nieodwiedzonych, wierzcho³kach
				if (weightMatrix[visitedVertices[j]][n] != infinity){ // sprawdzam, czy istnieje krawêdŸ
					if (!(find(visitedVertices.begin(), visitedVertices.end(), n) != visitedVertices.end())) { // sprawdzam, czy wierzcho³ek by³ ju¿ przegl¹dany - jeœli tak to przechodzê do kolejnego
						if (weightMatrix[visitedVertices[j]][n] < minimumFoundedValue) { // sprawdzam, czy znaleziona wartoœæ jest mniejsza od najmniejszej poprzedniej znalezionej
							firstVertex = j; // ustawiam na poprzedni wierzcho³ek, wierzcho³ek z którego wychodzi najkrótsza droga
							minimumFoundedValue = weightMatrix[visitedVertices[j]][n]; // na minimaln¹ wartoœæ ustawiam aktualnie przegl¹dany fragment macierzy wag
							nextVertex = n; // ustawiam na kolejny wierzcho³ek, wierzcho³ek do którego znalaz³em drogê
						}
					}
				}
			}
		}
		visitedVertices.push_back(nextVertex); // wrzucam do przegl¹dniêtych wierzcho³ków, wierzcho³ek do którego przyszed³em
		mst += minimumFoundedValue; // dodaje do mst znalezion¹ wartoœæ
		if (!isItTests)
			cout << "(" << visitedVertices[firstVertex] << ", " << nextVertex << ")" << "	" << minimumFoundedValue << endl;
	}
	if (!isItTests)
		cout << "MST = " << mst << endl;
}

void Graph::primsAlgorithmForList(bool isItTests) {

	for (int i = 0; i < adjacencyList.size(); i++) { // sortujemy listê
		adjacencyList[i].sort([](const AdjacencyListElement& element1, const AdjacencyListElement& element2) {
			return element1.weightOfEdge < element2.weightOfEdge;
			});
	}

	vector<int> visitedVertices; // tworzê tablicê, w której bêd¹ przechowywane odwiedzone wierzcho³ki
	int firstVertex = graphStart; // ustalam pierwszy wierzcho³ek (bêdzie on równie¿ odpowiada³ za wierzcho³ek, w którym aktualnie siê znajdujemy)
	visitedVertices.push_back(firstVertex); // i wrzucam go do odwiedzonych wierzcho³ków
	int nextVertex; // wierzcho³ek, który bêdzie odwiedzamy jako kolejny
	int mst = 0; // tutaj bêdzie przechowywane mst

	for (int i = 0; i < graphVertices - 1; i++) { // przegl¹dam graphVertices-1 wierzcho³ków, poniewa¿ jeden ju¿ wrzucony do visitedVertices
		float minimumFoundedValue = infinity; // t¹ zmienn¹ bêdziemy szukaæ najmniejszej wartoœci dlatego na pocz¹tku jest ustawiona na nieskoñczonoœæ

		for (int j = 0; j < (int)visitedVertices.size(); j++) { // przechodzê po odwiedzonych wierzcho³kach
			for (AdjacencyListElement element : adjacencyList[visitedVertices[j]]) { // przechodzê po wszystkich, równie¿ nieodwiedzonych, wierzcho³kach
				if (!(find(visitedVertices.begin(), visitedVertices.end(), element.destinationVertex) != visitedVertices.end())) { // sprawdzam, czy wierzcho³ek by³ ju¿ przegl¹dany - jeœli tak to przechodzê do kolejnego
					if (element.weightOfEdge < minimumFoundedValue) { // sprawdzam, czy znaleziona wartoœæ jest mniejsza od najmniejszej poprzedniej znalezionej
						firstVertex = j; // ustawiam na poprzedni wierzcho³ek, wierzcho³ek z którego wychodzi najkrótsza droga
						minimumFoundedValue = element.weightOfEdge; // na minimaln¹ wartoœæ ustawiam aktualnie przegl¹dany fragment listy s¹siedztwa
						nextVertex = element.destinationVertex; // ustawiam na kolejny wierzcho³ek, wierzcho³ek do którego znalaz³em drogê
					}
				}
			}
		}
		visitedVertices.push_back(nextVertex); // wrzucam do przegl¹dniêtych wierzcho³ków, wierzcho³ek do którego przyszed³em
		mst += minimumFoundedValue; // dodaje do mst znalezion¹ wartoœæ
		if (!isItTests)
			cout << "(" << visitedVertices[firstVertex] << ", " << nextVertex << ")" << "	" << minimumFoundedValue << endl;
	}
	if (!isItTests)
		cout << "MST = " << mst << endl;
}

void Graph::dijkstraAlgorithmForMatrix(bool isItTests) {
	if (minusWeight) { // sprawdzam czy sa ujemne wagi; jesli tak to konczy sprawdzanie
		cout << "W grafie znajduja sie ujemne wagi" << endl;
		return;
	}

	vector <float> distance; // tworze tablice przechowujaca drogi do wierzcholkow
	distance.resize(graphVertices, infinity); // ustawiam pocz¹tkowe œcie¿ki na wagê nieskoñczonoœæ
	vector<int> visitedVertices; // analogicznie jak przy algorymach Prima
	float minimumDistance;
	int index; // przechowuje wiadmoœæ o wierzcho³ku o najmniejszej wadze 
	vector<int> previousVertices; // tablica przechowujaca poprzednie wierzcholki
	previousVertices.resize(graphVertices, -1); // wypelniamy j¹ wartosciami -1, czyli zaden nie ma poprzedniego elementu

	distance[graphStart] = 0; // ustawiam wagê wierzcho³ka pocz¹tkowego na zero

	while (visitedVertices.size() < graphVertices) { // pêtla sprawdzaj¹ca wszystkie wierzcho³ki
		minimumDistance = infinity;
		for (int i = 0; i < distance.size(); i++) { // pêtla przechodzi po wszystkich wierzcho³kach i wybiera ten, do którego droga ma najmniejsz¹ wagê
			if (find(visitedVertices.begin(), visitedVertices.end(), i) != visitedVertices.end()) { // sprawedzenie czy wierzcholek by³ sprawdzany wczeœniej
				continue;
			}
			if (distance[i] < minimumDistance) { // wybieramy najkrotsza droge do wierzcho³ka
				minimumDistance = distance[i];
				index = i;
			}
		}
		visitedVertices.push_back(index); // wrzucamy wierzcho³ek o najmniejszej wadze do odwiedzonych (np. przy pierwszym przejsciu wierzcholek pocz¹tkowy, bo do niego droga wynosi 0)

		for (int i = 0; i < graphVertices; i++) { // sprawdzamy wszystkie wierzcholki
			if (weightMatrix[index][i] != infinity) { // jezeli z ktoryms wierzcholekiem mamy polaczenie (droga jest inna niz infinity)
				if (distance[index] + weightMatrix[index][i] < distance[i]) { // to sprawdzamy czy dystans dla elementu index i waga drogi jest mniejsza niz aktualnie zapisana droga (przy pierwszym przejsciu infinity)
					previousVertices[i] = index; // ustawiamy poprzedzajacy wierzcho³ek 
					distance[i] = distance[index] + weightMatrix[index][i]; // ustawiamy nowa wage dla sciezki
				}
			}
		}
	}

	if(!isItTests)
		showResult(distance, previousVertices);
}

void Graph::dijkstraAlgorithmForList(bool isItTests) {
	if (minusWeight) { // sprawdzam czy sa ujemne wagi; jesli tak to konczy sprawdzanie
		cout << "W grafie znajduja sie ujemne wagi" << endl;
		return;
	}

	vector <float> distance; // tworze tablice przechowujaca drogi do wierzcholkow
	distance.resize(graphVertices, infinity); // ustawiam pocz¹tkowe œcie¿ki na wagê nieskoñczonoœæ
	vector<int> visitedVertices; // analogicznie jak przy algorymach Prima
	float minimumDistance;
	int index; // przechowuje wiadmoœæ o wierzcho³ku o najmniejszej wadze 
	vector<int> previousVertices; // tablica przechowujaca poprzednie wierzcholki
	previousVertices.resize(graphVertices, -1); // wypelniamy j¹ wartosciami -1, czyli zaden nie ma poprzedniego elementu

	distance[graphStart] = 0; // ustawiam wagê wierzcho³ka pocz¹tkowego na zero

	while (visitedVertices.size() < graphVertices) { // pêtla sprawdzaj¹ca wszystkie wierzcho³ki
		minimumDistance = infinity;
		for (int i = 0; i < distance.size(); i++) { // pêtla przechodzi po wszystkich wierzcho³kach i wybiera ten, do którego droga ma najmniejsz¹ wagê
			if (find(visitedVertices.begin(), visitedVertices.end(), i) != visitedVertices.end()) { // sprawedzenie czy wierzcholek by³ sprawdzany wczeœniej
				continue;
			}
			if (distance[i] < minimumDistance) { // wybieramy najkrotsza droge do wierzcho³ka
				minimumDistance = distance[i];
				index = i;
			}
		}
		visitedVertices.push_back(index); // wrzucamy wierzcho³ek o najmniejszej wadze do odwiedzonych (np. przy pierwszym przejsciu wierzcholek pocz¹tkowy, bo do niego droga wynosi 0)

		for (AdjacencyListElement element : adjacencyList[index]) { // sprawdzamy wszystkie wierzcholki
			if (distance[index] + element.weightOfEdge < distance[element.destinationVertex]) { // to sprawdzamy czy dystans dla elementu index i waga drogi jest mniejsza niz aktualnie zapisana droga
				previousVertices[element.destinationVertex] = index; // ustawiamy poprzedzajacy wierzcho³ek 
				distance[element.destinationVertex] = distance[index] + weightMatrix[index][element.destinationVertex]; // ustawiamy nowa wage dla sciezki
			}
		}
	}

	if (!isItTests)
		showResult(distance, previousVertices);
}

void Graph::showResult(vector<float> distance, vector<int> previousVertices) {
	vector<int> displayInGoodOrder;

	for (int i = 0; i < graphVertices; i++) {
		cout << i << " | " << distance[i] << " | ";
		int j = i;

		while (previousVertices[j] != -1) {
			displayInGoodOrder.push_back(previousVertices[j]);
			j = previousVertices[j];
		}

		reverse(displayInGoodOrder.begin(), displayInGoodOrder.end());

		for (j = 0; j < displayInGoodOrder.size(); j++) {
			cout << displayInGoodOrder[j] << " ";
		}
		cout << i << " ";
		cout << endl;

		displayInGoodOrder.clear();
		displayInGoodOrder.resize(0);
	}
}

//metody na robienie testów do sprawozdania

void Graph::makeGraphForTestsWithDensity(int howMuchVertices, int whatDensity, bool isDirected) {
	int howMuchEdges = (howMuchVertices * (howMuchVertices - 1) / 2) * whatDensity / 100; // obliczam ilosc krawedzi na podstawie gestosci i ilosci wierzcholkow

	removeGraph(); // czyszczenie pamieci z poprzedniego grafu

	graphEdges = howMuchEdges; // wlasciwosci nowego grafu
	graphVertices = howMuchVertices;
	graphStart = 0;
	graphEnd = howMuchVertices-1;

	weightMatrix.resize(graphVertices, vector<float>(graphVertices, infinity));
	adjacencyList.resize(graphVertices);

	vector<int> notAddedToGraph; // tworzê tablice, ktora bêdzie przechowywala wierzcholki jeszcze niedodane do grafu

	for (int i = 0; i < howMuchVertices; i++) // pêtla dodaj¹ca wszystkie wierzcho³ki do jeszcze niedodanych do grafu
		notAddedToGraph.push_back(i);

	random_shuffle(notAddedToGraph.begin(), notAddedToGraph.end()); // losowanie, ¿eby za ka¿dym wywo³aniem funkcji dzia³o siê coœ innego

	int addedEdges = 0; // zmienna bêdzie liczy³a ile ju¿ jest dodanych krawêdzi; bêdzie potrzebna przy dope³nianiu grafu krawêdziami w celu osi¹gniêcia odpowienij gêstoœci
	vector<int> addedToGraph; // tworze tablice, w ktorej beda wierzcholki juz dodane do grafu

	addElementToGraph(notAddedToGraph[notAddedToGraph.size() - 1], notAddedToGraph[notAddedToGraph.size() - 2], rand() % 100, isDirected); // dodaje now¹ krawedz do grafu; biorê pod uwagê ostatnie wierzcho³ki, poniewa¿ o wiele ³atwiej jest ich siê pozbyæ z vectora funckj¹ pop_back()
	addedToGraph.push_back(notAddedToGraph.size() - 1); // dodaje do dodanych wierzcho³ek dodany
	notAddedToGraph.pop_back(); // jak jest w komentarzu dwie linijki wyzej - usuwam ostatni element, przed chwika dodany
	
	addedEdges++; // zwiekszamy licznik dodanych krawedzi
	// operacje wyzej nie s¹ w petli, poniewa¿ w petli krawedz dodajemy do juz dodanego wierzcholka do grafu, wiec potrzebujemy cos miec w tablicy addedToGraph

	while (notAddedToGraph.size() > 0) {
		addElementToGraph(notAddedToGraph[notAddedToGraph.size() - 1], addedToGraph[addedToGraph.size() - 1], rand() % 100, isDirected); // dodajemy krawedz do juz dodanego wierzcholka z jeszcze nie dodanego wierzcholka 
		addedToGraph.push_back(notAddedToGraph.size() - 1); // dodajemy kolejny wierzcholek
		notAddedToGraph.pop_back(); //usuwamy wierzcholek

		addedEdges++; // zwiekszamy licznik dodanych krawedzi
	}

	int firstVertex, destinationVertex;

	while (addedEdges < howMuchEdges) { // dope³niamy graf krawedziami, aby mial ich tyle, ile wymaga gêstoœæ
		random_shuffle(addedToGraph.begin(), addedToGraph.end()); // znowu shuffluje wierzcholki
		firstVertex = addedToGraph[addedToGraph.size() - 1]; // ustawiam ostatni
		destinationVertex = addedToGraph[addedToGraph.size() - 2]; // ustawiam przedostatni

		
		while (weightMatrix[firstVertex][destinationVertex] != infinity && weightMatrix[destinationVertex][firstVertex] != infinity) { // dopoki pojawia sie wartosc infinity (czyli krawedz nie istnieje)
			random_shuffle(addedToGraph.begin(), addedToGraph.end()); // analogicznie jak na pocz¹tku pierwszej pêtli while
			firstVertex = addedToGraph[addedToGraph.size() - 1]; 
			destinationVertex = addedToGraph[addedToGraph.size() - 2]; 
		} // i ponownie sprawdzamy czy istnieje juz ta krawedz

		addElementToGraph(firstVertex, destinationVertex, rand() % 100, isDirected); // dodajemy krawedz jeszcze nieistniejaca
		addedEdges++; // zwiekszamy licznik dodanych krawedzi
	}
}