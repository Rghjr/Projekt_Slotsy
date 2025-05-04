#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void UstawGrid(int** tablica, int rows, int cols);
    void LosujOdNowa();
    void WczytajPrawdopodobienstwa();
    int PrzypiszOwocek();  // Dodajemy deklarację funkcji PrzypiszOwocek()

    // Zmienna do przechowywania prawdopodobieństw
    int p_japko, p_banan, p_winogrono, p_wisnia, p_ananas, p_kiwi, p_bonus, sumaProporcji;

private:
    Ui::MainWindow *ui;
    QVector<QVector<QLabel*>> gridLabels;  // przechowujemy QLabel'e
};

#endif // MAINWINDOW_H
