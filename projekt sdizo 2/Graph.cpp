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
	cout << "Numer wierzcho�ka -> wierzcho�ek docelowy | waga �cie�ki" << endl;
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
	vector<int> visitedVertices; // tworz� tablic�, w kt�rej b�d� przechowywane odwiedzone wierzcho�ki
	int firstVertex = graphStart; // ustalam pierwszy wierzcho�ek (b�dzie on r�wnie� odpowiada� za wierzcho�ek, w kt�rym aktualnie si� znajdujemy)
	visitedVertices.push_back(firstVertex); // i wrzucam go do odwiedzonych wierzcho�k�w
	int nextVertex; // wierzcho�ek, kt�ry b�dzie odwiedzamy jako kolejny
	int mst = 0; // tutaj b�dzie przechowywane mst

	for (int i = 0; i < graphVertices - 1; i++) { // przegl�dam graphVertices-1 wierzcho�k�w, poniewa� jeden ju� wrzucony do visitedVertices
		float minimumFoundedValue = infinity; // t� zmienn� b�dziemy szuka� najmniejszej warto�ci dlatego na pocz�tku jest ustawiona na niesko�czono��

		for (int j = 0; j < (int) visitedVertices.size(); j++) { // przechodz� po odwiedzonych wierzcho�kach
			for (int n = 0; n < graphVertices; n++) { // przechodz� po wszystkich, r�wnie� nieodwiedzonych, wierzcho�kach
				if (weightMatrix[visitedVertices[j]][n] != infinity){ // sprawdzam, czy istnieje kraw�d�
					if (!(find(visitedVertices.begin(), visitedVertices.end(), n) != visitedVertices.end())) { // sprawdzam, czy wierzcho�ek by� ju� przegl�dany - je�li tak to przechodz� do kolejnego
						if (weightMatrix[visitedVertices[j]][n] < minimumFoundedValue) { // sprawdzam, czy znaleziona warto�� jest mniejsza od najmniejszej poprzedniej znalezionej
							firstVertex = j; // ustawiam na poprzedni wierzcho�ek, wierzcho�ek z kt�rego wychodzi najkr�tsza droga
							minimumFoundedValue = weightMatrix[visitedVertices[j]][n]; // na minimaln� warto�� ustawiam aktualnie przegl�dany fragment macierzy wag
							nextVertex = n; // ustawiam na kolejny wierzcho�ek, wierzcho�ek do kt�rego znalaz�em drog�
						}
					}
				}
			}
		}
		visitedVertices.push_back(nextVertex); // wrzucam do przegl�dni�tych wierzcho�k�w, wierzcho�ek do kt�rego przyszed�em
		mst += minimumFoundedValue; // dodaje do mst znalezion� warto��
		if (!isItTests)
			cout << "(" << visitedVertices[firstVertex] << ", " << nextVertex << ")" << "	" << minimumFoundedValue << endl;
	}
	if (!isItTests)
		cout << "MST = " << mst << endl;
}

void Graph::primsAlgorithmForList(bool isItTests) {

	for (int i = 0; i < adjacencyList.size(); i++) { // sortujemy list�
		adjacencyList[i].sort([](const AdjacencyListElement& element1, const AdjacencyListElement& element2) {
			return element1.weightOfEdge < element2.weightOfEdge;
			});
	}

	vector<int> visitedVertices; // tworz� tablic�, w kt�rej b�d� przechowywane odwiedzone wierzcho�ki
	int firstVertex = graphStart; // ustalam pierwszy wierzcho�ek (b�dzie on r�wnie� odpowiada� za wierzcho�ek, w kt�rym aktualnie si� znajdujemy)
	visitedVertices.push_back(firstVertex); // i wrzucam go do odwiedzonych wierzcho�k�w
	int nextVertex; // wierzcho�ek, kt�ry b�dzie odwiedzamy jako kolejny
	int mst = 0; // tutaj b�dzie przechowywane mst

	for (int i = 0; i < graphVertices - 1; i++) { // przegl�dam graphVertices-1 wierzcho�k�w, poniewa� jeden ju� wrzucony do visitedVertices
		float minimumFoundedValue = infinity; // t� zmienn� b�dziemy szuka� najmniejszej warto�ci dlatego na pocz�tku jest ustawiona na niesko�czono��

		for (int j = 0; j < (int)visitedVertices.size(); j++) { // przechodz� po odwiedzonych wierzcho�kach
			for (AdjacencyListElement element : adjacencyList[visitedVertices[j]]) { // przechodz� po wszystkich, r�wnie� nieodwiedzonych, wierzcho�kach
				if (!(find(visitedVertices.begin(), visitedVertices.end(), element.destinationVertex) != visitedVertices.end())) { // sprawdzam, czy wierzcho�ek by� ju� przegl�dany - je�li tak to przechodz� do kolejnego
					if (element.weightOfEdge < minimumFoundedValue) { // sprawdzam, czy znaleziona warto�� jest mniejsza od najmniejszej poprzedniej znalezionej
						firstVertex = j; // ustawiam na poprzedni wierzcho�ek, wierzcho�ek z kt�rego wychodzi najkr�tsza droga
						minimumFoundedValue = element.weightOfEdge; // na minimaln� warto�� ustawiam aktualnie przegl�dany fragment listy s�siedztwa
						nextVertex = element.destinationVertex; // ustawiam na kolejny wierzcho�ek, wierzcho�ek do kt�rego znalaz�em drog�
					}
				}
			}
		}
		visitedVertices.push_back(nextVertex); // wrzucam do przegl�dni�tych wierzcho�k�w, wierzcho�ek do kt�rego przyszed�em
		mst += minimumFoundedValue; // dodaje do mst znalezion� warto��
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
	distance.resize(graphVertices, infinity); // ustawiam pocz�tkowe �cie�ki na wag� niesko�czono��
	vector<int> visitedVertices; // analogicznie jak przy algorymach Prima
	float minimumDistance;
	int index; // przechowuje wiadmo�� o wierzcho�ku o najmniejszej wadze 
	vector<int> previousVertices; // tablica przechowujaca poprzednie wierzcholki
	previousVertices.resize(graphVertices, -1); // wypelniamy j� wartosciami -1, czyli zaden nie ma poprzedniego elementu

	distance[graphStart] = 0; // ustawiam wag� wierzcho�ka pocz�tkowego na zero

	while (visitedVertices.size() < graphVertices) { // p�tla sprawdzaj�ca wszystkie wierzcho�ki
		minimumDistance = infinity;
		for (int i = 0; i < distance.size(); i++) { // p�tla przechodzi po wszystkich wierzcho�kach i wybiera ten, do kt�rego droga ma najmniejsz� wag�
			if (find(visitedVertices.begin(), visitedVertices.end(), i) != visitedVertices.end()) { // sprawedzenie czy wierzcholek by� sprawdzany wcze�niej
				continue;
			}
			if (distance[i] < minimumDistance) { // wybieramy najkrotsza droge do wierzcho�ka
				minimumDistance = distance[i];
				index = i;
			}
		}
		visitedVertices.push_back(index); // wrzucamy wierzcho�ek o najmniejszej wadze do odwiedzonych (np. przy pierwszym przejsciu wierzcholek pocz�tkowy, bo do niego droga wynosi 0)

		for (int i = 0; i < graphVertices; i++) { // sprawdzamy wszystkie wierzcholki
			if (weightMatrix[index][i] != infinity) { // jezeli z ktoryms wierzcholekiem mamy polaczenie (droga jest inna niz infinity)
				if (distance[index] + weightMatrix[index][i] < distance[i]) { // to sprawdzamy czy dystans dla elementu index i waga drogi jest mniejsza niz aktualnie zapisana droga (przy pierwszym przejsciu infinity)
					previousVertices[i] = index; // ustawiamy poprzedzajacy wierzcho�ek 
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
	distance.resize(graphVertices, infinity); // ustawiam pocz�tkowe �cie�ki na wag� niesko�czono��
	vector<int> visitedVertices; // analogicznie jak przy algorymach Prima
	float minimumDistance;
	int index; // przechowuje wiadmo�� o wierzcho�ku o najmniejszej wadze 
	vector<int> previousVertices; // tablica przechowujaca poprzednie wierzcholki
	previousVertices.resize(graphVertices, -1); // wypelniamy j� wartosciami -1, czyli zaden nie ma poprzedniego elementu

	distance[graphStart] = 0; // ustawiam wag� wierzcho�ka pocz�tkowego na zero

	while (visitedVertices.size() < graphVertices) { // p�tla sprawdzaj�ca wszystkie wierzcho�ki
		minimumDistance = infinity;
		for (int i = 0; i < distance.size(); i++) { // p�tla przechodzi po wszystkich wierzcho�kach i wybiera ten, do kt�rego droga ma najmniejsz� wag�
			if (find(visitedVertices.begin(), visitedVertices.end(), i) != visitedVertices.end()) { // sprawedzenie czy wierzcholek by� sprawdzany wcze�niej
				continue;
			}
			if (distance[i] < minimumDistance) { // wybieramy najkrotsza droge do wierzcho�ka
				minimumDistance = distance[i];
				index = i;
			}
		}
		visitedVertices.push_back(index); // wrzucamy wierzcho�ek o najmniejszej wadze do odwiedzonych (np. przy pierwszym przejsciu wierzcholek pocz�tkowy, bo do niego droga wynosi 0)

		for (AdjacencyListElement element : adjacencyList[index]) { // sprawdzamy wszystkie wierzcholki
			if (distance[index] + element.weightOfEdge < distance[element.destinationVertex]) { // to sprawdzamy czy dystans dla elementu index i waga drogi jest mniejsza niz aktualnie zapisana droga
				previousVertices[element.destinationVertex] = index; // ustawiamy poprzedzajacy wierzcho�ek 
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

//metody na robienie test�w do sprawozdania

void Graph::makeGraphForTestsWithDensity(int howMuchVertices, int whatDensity, bool isDirected) {
	int howMuchEdges = (howMuchVertices * (howMuchVertices - 1) / 2) * whatDensity / 100; // obliczam ilosc krawedzi na podstawie gestosci i ilosci wierzcholkow

	removeGraph(); // czyszczenie pamieci z poprzedniego grafu

	graphEdges = howMuchEdges; // wlasciwosci nowego grafu
	graphVertices = howMuchVertices;
	graphStart = 0;
	graphEnd = howMuchVertices-1;

	weightMatrix.resize(graphVertices, vector<float>(graphVertices, infinity));
	adjacencyList.resize(graphVertices);

	vector<int> notAddedToGraph; // tworz� tablice, ktora b�dzie przechowywala wierzcholki jeszcze niedodane do grafu

	for (int i = 0; i < howMuchVertices; i++) // p�tla dodaj�ca wszystkie wierzcho�ki do jeszcze niedodanych do grafu
		notAddedToGraph.push_back(i);

	random_shuffle(notAddedToGraph.begin(), notAddedToGraph.end()); // losowanie, �eby za ka�dym wywo�aniem funkcji dzia�o si� co� innego

	int addedEdges = 0; // zmienna b�dzie liczy�a ile ju� jest dodanych kraw�dzi; b�dzie potrzebna przy dope�nianiu grafu kraw�dziami w celu osi�gni�cia odpowienij g�sto�ci
	vector<int> addedToGraph; // tworze tablice, w ktorej beda wierzcholki juz dodane do grafu

	addElementToGraph(notAddedToGraph[notAddedToGraph.size() - 1], notAddedToGraph[notAddedToGraph.size() - 2], rand() % 100, isDirected); // dodaje now� krawedz do grafu; bior� pod uwag� ostatnie wierzcho�ki, poniewa� o wiele �atwiej jest ich si� pozby� z vectora funckj� pop_back()
	addedToGraph.push_back(notAddedToGraph.size() - 1); // dodaje do dodanych wierzcho�ek dodany
	notAddedToGraph.pop_back(); // jak jest w komentarzu dwie linijki wyzej - usuwam ostatni element, przed chwika dodany
	
	addedEdges++; // zwiekszamy licznik dodanych krawedzi
	// operacje wyzej nie s� w petli, poniewa� w petli krawedz dodajemy do juz dodanego wierzcholka do grafu, wiec potrzebujemy cos miec w tablicy addedToGraph

	while (notAddedToGraph.size() > 0) {
		addElementToGraph(notAddedToGraph[notAddedToGraph.size() - 1], addedToGraph[addedToGraph.size() - 1], rand() % 100, isDirected); // dodajemy krawedz do juz dodanego wierzcholka z jeszcze nie dodanego wierzcholka 
		addedToGraph.push_back(notAddedToGraph.size() - 1); // dodajemy kolejny wierzcholek
		notAddedToGraph.pop_back(); //usuwamy wierzcholek

		addedEdges++; // zwiekszamy licznik dodanych krawedzi
	}

	int firstVertex, destinationVertex;

	while (addedEdges < howMuchEdges) { // dope�niamy graf krawedziami, aby mial ich tyle, ile wymaga g�sto��
		random_shuffle(addedToGraph.begin(), addedToGraph.end()); // znowu shuffluje wierzcholki
		firstVertex = addedToGraph[addedToGraph.size() - 1]; // ustawiam ostatni
		destinationVertex = addedToGraph[addedToGraph.size() - 2]; // ustawiam przedostatni

		
		while (weightMatrix[firstVertex][destinationVertex] != infinity && weightMatrix[destinationVertex][firstVertex] != infinity) { // dopoki pojawia sie wartosc infinity (czyli krawedz nie istnieje)
			random_shuffle(addedToGraph.begin(), addedToGraph.end()); // analogicznie jak na pocz�tku pierwszej p�tli while
			firstVertex = addedToGraph[addedToGraph.size() - 1]; 
			destinationVertex = addedToGraph[addedToGraph.size() - 2]; 
		} // i ponownie sprawdzamy czy istnieje juz ta krawedz

		addElementToGraph(firstVertex, destinationVertex, rand() % 100, isDirected); // dodajemy krawedz jeszcze nieistniejaca
		addedEdges++; // zwiekszamy licznik dodanych krawedzi
	}
}