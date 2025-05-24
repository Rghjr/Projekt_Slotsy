#ifndef GRA1MECHANIKI_H
#define GRA1MECHANIKI_H

#include "WarstwaBiznesowa_global.h"
#include <QtWidgets/QLabel>


class WARSTWABIZNESOWA_EXPORT Gra1Mechaniki
{
public:
    Gra1Mechaniki();
    ~Gra1Mechaniki();
    static QVector<QVector<int>> GenerujSymbole(int rows, int cols);

private:
};

#endif // GRA1MECHANIKI_H
