#ifndef OKNOGRA2_H
#define OKNOGRA2_H

#include <QMainWindow>
#include <QLabel>


QT_BEGIN_NAMESPACE
namespace Ui {
class OknoGra2;
}
QT_END_NAMESPACE

class OknoGra2 : public QMainWindow
{
    Q_OBJECT

public:
    OknoGra2(QWidget *parent = nullptr);
    ~OknoGra2();
    void UstawGrid(int **tablica, int rows, int cols);
    int PrzypiszOwocek();
    void LosujOdNowa();
    void WczytajPrawdopodobienstwa();
    void SprawdzWygrana();
    void AktualizujSaldo();
    float Winek(int x);

    int p_japko, p_banan, p_winogrono, p_wisnia, p_bonus, sumaProporcji;
    float w_japko, w_banan, w_winogrono, w_wisnia, w_bonus;
    float mn_bonus;
    int l_freespin, l_dodatkowychFreeSpinow;

    bool l1, l2, l3, l4, l5, l6, l7, l8, l9, l10, l11, l12, l13, l14, l15, l16, l17;

    void Autospin(bool checked);
    QTimer* autoSpinTimer = nullptr;

private slots:


private:
    Ui::OknoGra2 *ui;
    QVector<QVector<QLabel*>> gridLabels;
    float saldo = 100;
    int stawka = 5;

};

#endif // OKNOGRA2_H
