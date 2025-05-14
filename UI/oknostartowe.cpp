#include "oknostartowe.h"
#include "oknogra1.h"
#include "ui_oknostartowe.h"
#include <QProcess>
#include <QFile>
#include <QMessageBox>
#include <cstdlib>
#include <QApplication>
#include <qapplication.h>


OknoStartowe::OknoStartowe(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::OknoStartowe)
{
    ui->setupUi(this);
    this->setFixedSize(560, 400); //Stały rozmiar

    QPixmap logo(QCoreApplication::applicationDirPath() + "/../../logo.png"); // Ścieżka do pliku
    ui->logoLabel->setPixmap(logo); // Użycie istniejącego QLabel
    ui->logoLabel->setScaledContents(false); // Dopasowanie do rozmiaru
    ui->logoLabel->setAlignment(Qt::AlignCenter); // Wyśrodkowanie
}

OknoStartowe::~OknoStartowe()
{
    delete ui;
}

void OknoStartowe::on_firstGameButton_clicked()
{
    close(); //Zamknięcie okna

    int rows = 5, cols = 6;
    int **tablica = new int *[rows];
    for (int i = 0; i < rows; ++i) {
        tablica[i] = new int[cols];
    }

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            tablica[i][j] = rand() % 7; // Możesz to zostawić jak było, ale używasz już dynamicznych progów

    OknoGra1 *gra = new OknoGra1(); // Tworzenia okna z grą
    gra->show();
    gra->UstawGrid(tablica, rows, cols);

    for (int i = 0; i < rows; ++i)
        delete[] tablica[i];
    delete[] tablica;
}

void OknoStartowe::on_secondGameButton_clicked()
{

}

void OknoStartowe::on_exitButton_clicked()
{
    close(); //Zamknięcie okna
}







