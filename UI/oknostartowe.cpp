#include "oknostartowe.h"
#include "oknogra1.h"
#include "oknogra2.h"
#include "ui_oknostartowe.h"
#include "gra1mechaniki.h"
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
    ui->SaldoLabel->setText(QString("Saldo: %1").arg(saldo));
    connect(ui->plusButton, &QPushButton::clicked, this, &OknoStartowe::EdytujSaldoPlus);
    connect(ui->minusButton, &QPushButton::clicked, this, &OknoStartowe::EdytujSaldoMinus);
}

OknoStartowe::~OknoStartowe()
{
    delete ui;
}

void OknoStartowe::on_firstGameButton_clicked()
{
    hide(); // Ukrywamy okno

    int rows = 5, cols = 6;
    QVector<QVector<int>> tablica = Gra1Mechaniki::GenerujSymbole(rows, cols); // Generacja symboli

    OknoGra1 *gra = new OknoGra1(); // Tworzymy nowe okno gry
    gra->setAttribute(Qt::WA_DeleteOnClose); // Zapewniamy automatyczne usunięcie po zamknięciu
    gra->show();
    gra->UstawGrid(tablica, rows, cols);

}

void OknoStartowe::on_secondGameButton_clicked()
{
    hide();

    int rows = 3, cols = 3;
    int **tablica = new int *[rows];
    for (int i = 0; i < rows; ++i) {
        tablica[i] = new int[cols];
    }

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            tablica[i][j] = rand() % 7;

    OknoGra2 *gra = new OknoGra2(this, nullptr);        // Tworzenia okna z grą
    gra->show();
    gra->UstawGrid(tablica, rows, cols);

    for (int i = 0; i < rows; ++i)
        delete[] tablica[i];
    delete[] tablica;
}

void OknoStartowe::on_exitButton_clicked()
{
    close(); //Zamknięcie okna
}

void OknoStartowe::EdytujSaldoPlus()
{
    bool ok;
    float amount = ui->amountQLineEdit->text().toFloat(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Błąd", "Podaj poprawną liczbę!");
        return;
    }
    saldo += amount;
    ui->SaldoLabel->setText(QString("Saldo: %1").arg(saldo));
}

void OknoStartowe::EdytujSaldoMinus()
{
    bool ok;
    float amount = ui->amountQLineEdit->text().toFloat(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Błąd", "Podaj poprawną liczbę!");
        return;
    }
    saldo -= amount;
    if (saldo < 0)
    {
        saldo = 0;
        QMessageBox::warning(this, "Błąd", "Nie można zejść poniżej zera!");
    }

    ui->SaldoLabel->setText(QString("Saldo: %1").arg(saldo));
}


