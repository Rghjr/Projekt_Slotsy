#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void UstawGrid(int **tablica, int rows, int cols);
    void AnimujGrawitacje();
    void Autospin(bool checked);
    void UsunPolaczoneOwoce(QString a);
    void LosujOdNowa();
    void WczytajPrawdopodobienstwa();
    int PrzypiszOwocek(); // Dodajemy deklarację funkcji PrzypiszOwocek()
    void AktualizujSaldo();
    void SprawdzWygrana();
    void ZwiekszStawke();
    void ZmniejszStawke();

    // Zmienna do przechowywania prawdopodobieństw
    int p_japko, p_banan, p_winogrono, p_wisnia, p_ananas, p_kiwi, p_bonus, sumaProporcji;
    int l_japko, l_banan, l_winogrono, l_wisnia, l_ananas, l_kiwi, l_bonus;
    float w_japko, w_banan, w_winogrono, w_wisnia, w_ananas, w_kiwi;
    QTimer* autoSpinTimer = nullptr;


private:
    Ui::MainWindow *ui;
    QVector<QVector<QLabel *>> gridLabels; // przechowujemy QLabel'e
    float saldo = 100;
    int stawka = 5;
};

#endif // MAINWINDOW_H
