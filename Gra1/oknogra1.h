#ifndef OKNOGRA1_H
#define OKNOGRA1_H

#include "oknostartowe.h"
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
    OknoGra1(OknoStartowe* startoweOkno, QWidget *parent = nullptr);
    virtual ~OknoGra1();
    virtual void UstawGrid(const QVector<QVector<int>>& tablica, int rows, int cols);
    virtual void Autospin(bool checked);
    virtual void LosujOdNowa();
    virtual void WczytajPrawdopodobienstwa();
    virtual int PrzypiszOwocek();
    virtual void AktualizujSaldo();
    virtual void SprawdzWygrana();
    virtual void ZapisDoPliku();
    virtual bool WczytanieZPliku();

    static QVector<QVector<int>> GenerujSymbole(int rows, int cols);

    void Bonus();
    void ZwiekszStawke();
    void ZmniejszStawke();
    void AnimujGrawitacje();
    void UsunPolaczoneOwoce(QString a);

    QTimer* autoSpinTimer = nullptr;

private slots:
    void on_returnButton_select();

private:
    Ui::OknoGra1 *ui;
    OknoStartowe* oknoStartowe;
    QVector<QVector<QLabel *>> gridLabels; // przechowujemy QLabel'e
    float saldo;
    int stawka = 5;

    // Zmienna do przechowywania prawdopodobieństw
    int p_japko, p_banan, p_winogrono, p_wisnia, p_ananas, p_kiwi, p_bonus, sumaProporcji;
    int l_japko, l_banan, l_winogrono, l_wisnia, l_ananas, l_kiwi, l_bonus;
    int l_freespin, l_dodatkowychFreeSpinow;
    bool bonus;
    int freespiny;
    float w_japko, w_banan, w_winogrono, w_wisnia, w_ananas, w_kiwi;
};

#endif // OKNOGRA1_H
