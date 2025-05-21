#ifndef OKNOGRA1_H
#define OKNOGRA1_H

#include "gra1mechaniki.h"
#include <QLabel>
#include <QMainWindow>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui {
class OknoGra1;
}
QT_END_NAMESPACE

class OknoGra1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit OknoGra1(QWidget *parent = nullptr);
    ~OknoGra1();
    void UstawGrid(QVector<QVector<int>> tablica, int rows, int cols);
    void AnimujGrawitacje();
    void Autospin(bool checked);
    void UsunPolaczoneOwoce(QString a);
    void LosujOdNowa();
    void WczytajPrawdopodobienstwa();
    void AktualizujSaldo();
    void SprawdzWygrana();
    void Bonus();
    void ZwiekszStawke();
    void ZmniejszStawke();

    QTimer* autoSpinTimer = nullptr;


private:
    Ui::OknoGra1 *ui;
    QVector<QVector<QLabel *>> gridLabels; // przechowujemy QLabel'e
    Gra1Mechaniki* mechanika;
    float saldo = 100;
    int stawka = 5;
    int sumaProporcji;
};

#endif // OKNOGRA1_H
