#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    srand(time(nullptr));

    int rows = 5, cols = 6;
    int** tablica = new int* [rows];
    for (int i = 0; i < rows; ++i)
    {
        tablica[i] = new int[cols];
    }

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            tablica[i][j] = rand() % 7;  // Możesz to zostawić jak było, ale używasz już dynamicznych progów

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.UstawGrid(tablica, rows, cols);

    for (int i = 0; i < rows; ++i)
        delete[] tablica[i];
    delete[] tablica;

    return a.exec();
}
