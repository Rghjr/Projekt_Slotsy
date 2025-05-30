#include "oknostartowe.h"
#include "Gra1/oknogra1.h"
#include "Gra2/oknogra2.h"
#include "ui_oknostartowe.h"
#include "obslugawyjatkow.h"
#include <QProcess>
#include <QFile>
#include <QMessageBox>
#include <QApplication>
#include <qapplication.h>
#include <QListWidget>


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
    connect(ui->plusButton, &QPushButton::clicked, this, &OknoStartowe::EdytujSaldoPlus);
    connect(ui->minusButton, &QPushButton::clicked, this, &OknoStartowe::EdytujSaldoMinus);

    WczytajDaneGra1();
    WczytajDaneGra2();
    WczytajSaldo();

}

OknoStartowe::~OknoStartowe()
{
    delete ui;
}

void OknoStartowe::on_firstGameButton_clicked()
{
    hide(); // Ukrywamy okno

    int rows = 5, cols = 6;
    QVector<QVector<int>> tablica = OknoGra1::GenerujSymbole(rows, cols); // Generacja symboli

    OknoGra1 *gra = new OknoGra1(this, nullptr); // Tworzymy nowe okno gry
    gra->setAttribute(Qt::WA_DeleteOnClose); // Zapewniamy automatyczne usunięcie po zamknięciu
    gra->show();
    gra->UstawGrid(tablica, rows, cols);

}

void OknoStartowe::on_secondGameButton_clicked()
{
    hide();

    int rows = 3, cols = 3;
    QVector<QVector<int>> tablica = OknoGra1::GenerujSymbole(rows, cols);

    OknoGra1 *gra = new OknoGra2(this, nullptr); // Tworzenia okna z grą
    gra->setAttribute(Qt::WA_DeleteOnClose);
    gra->show();
    gra->UstawGrid(tablica, rows, cols);
}

void OknoStartowe::on_exitButton_clicked()
{
    close(); //Zamknięcie okna
}

void OknoStartowe::EdytujSaldoPlus()
{
    try {
    bool ok;
    float amount = ui->amountQLineEdit->text().toFloat(&ok);
    if (!ok) throw ZlyInput();
    saldo += amount;
    AktualizujSaldo();
    } catch (std::exception& ZlyInput)
    {
        QMessageBox::warning(this, "Błąd wejścia", ZlyInput.what());
        return;
    }
}

void OknoStartowe::EdytujSaldoMinus()
{
    try {
    bool ok;
    float amount = ui->amountQLineEdit->text().toFloat(&ok);

    if (!ok) throw ZlyInput();

    saldo -= amount;

    if (saldo < 0) throw PonizejZera();

    AktualizujSaldo();
    } catch (const ZlyInput& ZlyInput)
    {
        QMessageBox::warning(this, "Błąd wejścia", ZlyInput.what());
        return;
    }
    catch (const PonizejZera& PonizejZera)
    {
        QMessageBox::warning(this, "Błąd wejścia", PonizejZera.what());
        return;
    }
}

void OknoStartowe::AktualizujSaldo()
{
    QFile file("Saldo.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << saldo << "\n";
        file.close();
    } else {
        qWarning("Nie można otworzyć pliku Saldo.txt do zapisu");
    }
    ui->SaldoLabel->setText(QString("Saldo: %1").arg(saldo));
}

void OknoStartowe::WczytajSaldo()
{
    QFile file("Saldo.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString line = in.readLine().trimmed();
        bool ok = false;
        float wczytaneSaldo = line.toFloat(&ok);
        if (ok) {
            saldo = wczytaneSaldo;
        } else {
            saldo = 100.0f;  // albo jakaś wartość domyślna, gdy plik jest uszkodzony
        }
        file.close();
    } else {
        saldo = 100.0f;  // jeśli pliku nie ma, saldo zaczynamy od 0
    }
    ui->SaldoLabel->setText(QString("Saldo: %1").arg(saldo));
}

void OknoStartowe::WczytajDaneGra1()
{
    QFile file("wygrane_1.txt");

    if (!file.exists()) //sprawdzanie czy plik istnieje
    {
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream out(&file);
            file.close();
        }
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Nie można otworzyć pliku wygrane_1.txt");
        return;
    }

    ui->Gra_1_listWidget->clear();

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty()) {
            ui->Gra_1_listWidget->addItem(line);
        }
    }

    file.close();
}

void OknoStartowe::WczytajDaneGra2()
{
    QFile file("wygrane_2.txt");

    if (!file.exists()) //sprawdzanie czy plik istnieje
    {
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream out(&file);
            file.close();
        }
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Nie można otworzyć pliku wygrane_2.txt");
        return;
    }

    ui->Gra_2_listWidget->clear();

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty()) {
            ui->Gra_2_listWidget->addItem(line);
        }
    }

    file.close();
}

