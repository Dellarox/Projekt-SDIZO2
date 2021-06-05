#include <iostream>
#include "Graph.h"

using namespace std;

int main(){
    setlocale(LC_ALL, "polish");

    int whatToDoMenu = 0;
    char continueOfMain = 'x';
    bool backToMainMenu;
    string fileName;
    Graph g;

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

            if (g.fileReadGraph(fileName, true)) {
                cout << "Nie ma takiego pliku!" << endl;
                system("pause");
                break;
            }

            cout << "1. Algorytm Prima." << endl;
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
            cout << "2. Algorytm Dijkstry." << endl;
            g.dijkstraAlgorithmForMatrix(true);
            cout << endl << endl;
            g.dijkstraAlgorithmForList(true);
            cout << endl << endl;
        }

        cout << "Czy chcesz kontynuowac? (T/N)" << endl;
        cin >> continueOfMain;
    } while (continueOfMain == 'T' || continueOfMain == 't');
}