#include "gra1mechaniki.h"
#include <QVector>
#include <QMap>
#include <QtWidgets/qlabel.h>

Gra1Mechaniki::Gra1Mechaniki() {

}

Gra1Mechaniki::~Gra1Mechaniki() {

}

QVector<QVector<int>> Gra1Mechaniki::GenerujSymbole(int rows, int cols) {
    QVector<QVector<int>> tablica(rows, QVector<int>(cols)); // Tworzymy dwuwymiarowy wektor o wymiarach rows na cols

    for (int i = 0; i < rows; ++i) // Wypełniamy każdy element losową wartością od 0 do 6 (indeksy symboli)
        for (int j = 0; j < cols; ++j)
            tablica[i][j] = rand() % 7;

    return tablica;
}
