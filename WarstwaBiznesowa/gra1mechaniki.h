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
    int PrzypiszOwocek(); // Dodajemy deklarację funkcji PrzypiszOwocek()
    void UstawPrawdopodobienstwa(int japko, int banan, int winogrono, int wisnia,
                                 int ananas, int kiwi, int bonus,
                                 int l_freespin, int l_dodatkowychFreeSpinow,
                                 int l_japko, int l_banan, int l_winogrono, int l_wisnia,
                                 int l_ananas, int l_kiwi, int l_bonus,
                                 float w_japko, float w_banan, float w_winogrono, float w_wisnia,
                                 float w_ananas, float w_kiwi);

    int PobierzSumaProporcji() const; //możliwość pobrania wartości sumaProporcji
    QMap<QString, QPair<int, float>> SprawdzWygranaMechanika(const QVector<QVector<QString>>& siatkaTekstow, float stawka);
    QMap<QString, QPair<int, float>> BonusMechanika(const QVector<QVector<QString>>& siatkaTekstow, int l_freespin, int l_dodatkowychFreeSpinow, float stawka);

    int PobierzLiczbeFreeSpinow() const;
    int PobierzLiczbeDodatkowychFreeSpinow() const;

private:
    // Zmienna do przechowywania prawdopodobieństw
    int p_japko, p_banan, p_winogrono, p_wisnia, p_ananas, p_kiwi, p_bonus, sumaProporcji;
    int l_japko, l_banan, l_winogrono, l_wisnia, l_ananas, l_kiwi, l_bonus;
    float w_japko, w_banan, w_winogrono, w_wisnia, w_ananas, w_kiwi;
    int l_freespiny, l_dodatkowychFreeSpinow;
};

#endif // GRA1MECHANIKI_H
