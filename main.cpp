#include <QApplication>
#include <cstdlib>
#include <ctime>
#include "UI/oknostartowe.h"
#include "oknostartowe.h"


int main(int argc, char *argv[])
{
    srand(time(nullptr));

    QApplication a(argc, argv);
    OknoStartowe w;
    w.show();

    return a.exec();
}
