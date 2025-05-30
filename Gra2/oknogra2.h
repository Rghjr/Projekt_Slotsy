#ifndef OKNOGRA2_H
#define OKNOGRA2_H

#include "oknostartowe.h"
#include <QMainWindow>
#include <QLabel>
#include <Gra1/oknogra1.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class OknoGra2;
}
QT_END_NAMESPACE

class OknoGra2 : public OknoGra1
{
    Q_OBJECT

public:
    OknoGra2(OknoStartowe* startoweOkno, QWidget *parent = nullptr);
    ~OknoGra2();
    void UstawGrid(const QVector<QVector<int>>& tablica, int rows, int cols) override;
    int PrzypiszOwocek() override;
    void LosujOdNowa() override;
    void WczytajPrawdopodobienstwa() override;
    void SprawdzWygrana() override;
    void AktualizujSaldo() override;
    void Autospin(bool checked) override;
    void ZapisDoPliku() override;
    bool WczytanieZPliku() override;

    void SprawdzWygranaBonus();
    float Winek(int x);
    void zmienStawke(const QString &tekst);

private slots:
    void on_returnButton_select();

private:
    Ui::OknoGra2 *ui;
    OknoStartowe* oknoStartowe;
    QVector<QVector<QLabel*>> gridLabels;

    float saldo;
    float stawka = 5;

    int p_japko, p_banan, p_winogrono, p_wisnia, p_bonus, sumaProporcji;
    float w_japko, w_banan, w_winogrono, w_wisnia, w_bonus;
    float mn_bonus;
    int l_freespin, l_dodatkowychFreeSpinow;

    bool l1, l2, l3, l4, l5, l6, l7, l8, l9, l10, l11, l12, l13, l14, l15, l16, l17;
    bool bonus;
    int spiny_bonus;
};

#endif // OKNOGRA2_H
