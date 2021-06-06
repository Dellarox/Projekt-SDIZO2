#include <iostream>
#include "TimeTests.h"
#include "Graph.h"

using namespace std;

int main(){
    setlocale(LC_ALL, "polish");

    int whatToDoMenu = 0;
    char continueOfMain = 'x';
    bool backToMainMenu;
    string fileName;
    Graph g;
    TimeTests tt;
    bool checker;

    do {
        system("cls");
        backToMainMenu = true;

        cout << "Projekt SDiZO    Kajetan Krasoń    252767" << endl;
        cout << "1. Wczytanie struktury grafu z pliku." << endl;
        cout << "2. Testy." << endl;
        cin >> whatToDoMenu;
        cout << endl;

        switch (whatToDoMenu) {
        case 1:
            cout << "Podaj nazwę pliku: " << endl;
            cin >> fileName;
            checker = g.fileReadGraph(fileName, false);

            if (!checker) {
                cout << "Nie ma takiego pliku!" << endl;
                system("pause");
                return 0;
            }

            cout << "1. Algorytm Prima - graf skierowany." << endl;
            cout << "Macierz wag: " << endl << endl;
            g.showWeightMatrix();
            cout << endl << endl;
            cout << "Lista sąsiedztwa: " << endl << endl;
            g.showAdjacencyList();
            cout << endl << endl << "Edge    Weight" << endl;
            g.primsAlgorithmForMatrix(false);
            cout << endl << endl << "Edge    Weight" << endl;
            g.primsAlgorithmForList(false);
            cout << endl << endl;

            g.fileReadGraph(fileName, true);
            cout << "2. Algorytm Dijkstry - graf nieskierowany." << endl;
            cout << "Macierz wag: " << endl << endl;
            g.showWeightMatrix();
            cout << endl << endl;
            cout << "Lista sąsiedztwa: " << endl << endl;
            g.showAdjacencyList();
            cout << endl << endl << "End Dist Path" << endl;
            g.dijkstraAlgorithmForMatrix(false);
            cout << endl << endl << "End Dist Path" << endl;
            g.dijkstraAlgorithmForList(false);
            cout << endl << endl;
            break;
        case 2:
            /*cout << "Test algorytmu Prima dla macierzy wag: " << endl;
            tt.timeTestsForPrimsAlgorithmOnMatrix(g, 25, 25);
            tt.timeTestsForPrimsAlgorithmOnMatrix(g, 25, 50);
            tt.timeTestsForPrimsAlgorithmOnMatrix(g, 25, 75);
            tt.timeTestsForPrimsAlgorithmOnMatrix(g, 25, 99);
            cout << endl << endl;
            tt.timeTestsForPrimsAlgorithmOnMatrix(g, 50, 25);
            tt.timeTestsForPrimsAlgorithmOnMatrix(g, 50, 50);
            tt.timeTestsForPrimsAlgorithmOnMatrix(g, 50, 75);
            tt.timeTestsForPrimsAlgorithmOnMatrix(g, 50, 99);
            cout << endl << endl;
            tt.timeTestsForPrimsAlgorithmOnMatrix(g, 75, 25);
            tt.timeTestsForPrimsAlgorithmOnMatrix(g, 75, 50);
            tt.timeTestsForPrimsAlgorithmOnMatrix(g, 75, 75);
            tt.timeTestsForPrimsAlgorithmOnMatrix(g, 75, 99);
            cout << endl << endl;
            tt.timeTestsForPrimsAlgorithmOnMatrix(g, 100, 25);
            tt.timeTestsForPrimsAlgorithmOnMatrix(g, 100, 50);
            tt.timeTestsForPrimsAlgorithmOnMatrix(g, 100, 75);
            tt.timeTestsForPrimsAlgorithmOnMatrix(g, 100, 99);
            cout << endl << endl;
            tt.timeTestsForPrimsAlgorithmOnMatrix(g, 200, 25);
            tt.timeTestsForPrimsAlgorithmOnMatrix(g, 200, 50);
            tt.timeTestsForPrimsAlgorithmOnMatrix(g, 200, 25);
            tt.timeTestsForPrimsAlgorithmOnMatrix(g, 200, 99);
            cout << endl << endl;
            cout<<"Test algorytmu Prima dla listy sąsiedztwa: " << endl;
            tt.timeTestsForPrimsAlgorithmOnList(g, 25, 25);
            tt.timeTestsForPrimsAlgorithmOnList(g, 25, 50);
            tt.timeTestsForPrimsAlgorithmOnList(g, 25, 75);
            tt.timeTestsForPrimsAlgorithmOnList(g, 25, 99);
            cout << endl << endl;
            tt.timeTestsForPrimsAlgorithmOnList(g, 50, 25);
            tt.timeTestsForPrimsAlgorithmOnList(g, 50, 50);
            tt.timeTestsForPrimsAlgorithmOnList(g, 50, 75);
            tt.timeTestsForPrimsAlgorithmOnList(g, 50, 99);
            cout << endl << endl;
            tt.timeTestsForPrimsAlgorithmOnList(g, 75, 25);
            tt.timeTestsForPrimsAlgorithmOnList(g, 75, 50);
            tt.timeTestsForPrimsAlgorithmOnList(g, 75, 75);
            tt.timeTestsForPrimsAlgorithmOnList(g, 75, 99);
            cout << endl << endl;
            tt.timeTestsForPrimsAlgorithmOnList(g, 100, 25);
            tt.timeTestsForPrimsAlgorithmOnList(g, 100, 50);
            tt.timeTestsForPrimsAlgorithmOnList(g, 100, 75);
            tt.timeTestsForPrimsAlgorithmOnList(g, 100, 99);
            cout << endl << endl;
            tt.timeTestsForPrimsAlgorithmOnList(g, 200, 25);
            tt.timeTestsForPrimsAlgorithmOnList(g, 200, 50);
            tt.timeTestsForPrimsAlgorithmOnList(g, 200, 25);
            tt.timeTestsForPrimsAlgorithmOnList(g, 200, 99);
            cout << endl << endl;*/
            cout << "Test algorytmu Dijkstry dla macierzy wag: " << endl;
            tt.timeTestsForDijsktraAlgorithmOnMatrix(g, 25, 25);
            tt.timeTestsForDijsktraAlgorithmOnMatrix(g, 25, 50);
            tt.timeTestsForDijsktraAlgorithmOnMatrix(g, 25, 75);
            tt.timeTestsForDijsktraAlgorithmOnMatrix(g, 25, 99);
            cout << endl << endl;
            tt.timeTestsForDijsktraAlgorithmOnMatrix(g, 50, 25);
            tt.timeTestsForDijsktraAlgorithmOnMatrix(g, 50, 50);
            tt.timeTestsForDijsktraAlgorithmOnMatrix(g, 50, 75);
            tt.timeTestsForDijsktraAlgorithmOnMatrix(g, 50, 99);
            cout << endl << endl;
            tt.timeTestsForDijsktraAlgorithmOnMatrix(g, 75, 25);
            tt.timeTestsForDijsktraAlgorithmOnMatrix(g, 75, 50);
            tt.timeTestsForDijsktraAlgorithmOnMatrix(g, 75, 75);
            tt.timeTestsForDijsktraAlgorithmOnMatrix(g, 75, 99);
            cout << endl << endl;
            tt.timeTestsForDijsktraAlgorithmOnMatrix(g, 100, 25);
            tt.timeTestsForDijsktraAlgorithmOnMatrix(g, 100, 50);
            tt.timeTestsForDijsktraAlgorithmOnMatrix(g, 100, 75);
            tt.timeTestsForDijsktraAlgorithmOnMatrix(g, 100, 99);
            cout << endl << endl;
            tt.timeTestsForDijsktraAlgorithmOnMatrix(g, 200, 25);
            tt.timeTestsForDijsktraAlgorithmOnMatrix(g, 200, 50);
            tt.timeTestsForDijsktraAlgorithmOnMatrix(g, 200, 25);
            tt.timeTestsForDijsktraAlgorithmOnMatrix(g, 200, 99);
            cout << endl << endl;
            cout << "Test algorytmu Dijkstry dla listy sąsiedztwa: " << endl;
            tt.timeTestsForDijsktraAlgorithmOnList(g, 25, 25);
            tt.timeTestsForDijsktraAlgorithmOnList(g, 25, 50);
            tt.timeTestsForDijsktraAlgorithmOnList(g, 25, 75);
            tt.timeTestsForDijsktraAlgorithmOnList(g, 25, 99);
            cout << endl << endl;
            tt.timeTestsForDijsktraAlgorithmOnList(g, 50, 25);
            tt.timeTestsForDijsktraAlgorithmOnList(g, 50, 50);
            tt.timeTestsForDijsktraAlgorithmOnList(g, 50, 75);
            tt.timeTestsForDijsktraAlgorithmOnList(g, 50, 99);
            cout << endl << endl;
            tt.timeTestsForDijsktraAlgorithmOnList(g, 75, 25);
            tt.timeTestsForDijsktraAlgorithmOnList(g, 75, 50);
            tt.timeTestsForDijsktraAlgorithmOnList(g, 75, 75);
            tt.timeTestsForDijsktraAlgorithmOnList(g, 75, 99);
            cout << endl << endl;
            tt.timeTestsForDijsktraAlgorithmOnList(g, 100, 25);
            tt.timeTestsForDijsktraAlgorithmOnList(g, 100, 50);
            tt.timeTestsForDijsktraAlgorithmOnList(g, 100, 75);
            tt.timeTestsForDijsktraAlgorithmOnList(g, 100, 99);
            cout << endl << endl;
            tt.timeTestsForDijsktraAlgorithmOnList(g, 200, 25);
            tt.timeTestsForDijsktraAlgorithmOnList(g, 200, 50);
            tt.timeTestsForDijsktraAlgorithmOnList(g, 200, 25);
            tt.timeTestsForDijsktraAlgorithmOnList(g, 200, 99);
            cout << endl << endl;
        }

        cout << "Czy chcesz kontynuowac? (T/N)" << endl;
        cin >> continueOfMain;
    } while (continueOfMain == 'T' || continueOfMain == 't');
}