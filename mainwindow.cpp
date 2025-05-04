#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Ustawienie początkowych wartości w polach edycyjnych
    ui->JapkoEdit->setText("30");
    ui->BananEdit->setText("20");
    ui->WinogronkoEdit->setText("15");
    ui->WisniaEdit->setText("13");
    ui->AnanasEdit->setText("10");
    ui->KiwiEdit->setText("8");
    ui->BonusEdit->setText("4");



    ui->liczbaSymboliLineEdit_Japko->setText("8");   // Tu ustawiłeś liczbę symboli dla jabłka
    ui->liczbaSymboliLineEdit_Banan->setText("8");   // Liczba symboli dla banana
    ui->liczbaSymboliLineEdit_Winogronko->setText("8");  // Liczba symboli dla winogronka
    ui->liczbaSymboliLineEdit_Wisnia->setText("8");  // Liczba symboli dla wiśni
    ui->liczbaSymboliLineEdit_Ananas->setText("8");  // Liczba symboli dla ananasa
    ui->liczbaSymboliLineEdit_Kiwi->setText("8");    // Liczba symboli dla kiwi
    ui->liczbaSymboliLineEdit_Bonus->setText("4");   // Liczba symboli dla bonusu

    // Ustawienie początkowych wartości wygranych (jeśli też chcesz je ustawić na etykietach)
    ui->kwotaWygranejLineEdit_Japko->setText("0.75");  // Kwota wygranej dla jabłka
    ui->kwotaWygranejLineEdit_Banan->setText("1.25");  // Kwota wygranej dla banana
    ui->kwotaWygranejLineEdit_Winogronko->setText("2");  // Kwota wygranej dla winogronka
    ui->kwotaWygranejLineEdit_Wisnia->setText("3");  // Kwota wygranej dla wiśni
    ui->kwotaWygranejLineEdit_Ananas->setText("5");  // Kwota wygranej dla ananasa
    ui->kwotaWygranejLineEdit_Kiwi->setText("8");   // Kwota wygranej dla kiwi

    // Ładowanie prawdopodobieństw (już z początkowymi wartościami)
    WczytajPrawdopodobienstwa();

    // Połączenie przycisku z funkcją
    connect(ui->SPINPRZYCISK, &QPushButton::clicked, this, &MainWindow::LosujOdNowa);

    ui->StawkaLabel->setText("Stawka: 5");
    connect(ui->plusButton, &QPushButton::clicked, this, &MainWindow::ZwiekszStawke);
    connect(ui->minusButton, &QPushButton::clicked, this, &MainWindow::ZmniejszStawke);

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UstawGrid(int** tablica, int rows, int cols)
{
    QStringList owoce = { "🍎", "🍌", "🍇", "🍒", "🍍", "🥝", "🎁" };

    // wyczyść poprzednie widgety z layoutu
    QLayoutItem* item;
    while ((item = ui->maszyna->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    gridLabels.resize(rows);
    for (int i = 0; i < rows; ++i)
    {
        gridLabels[i].resize(cols);
        for (int j = 0; j < cols; ++j)
        {
            int wartosc = tablica[i][j];
            QLabel* label = new QLabel(owoce[wartosc]);
            label->setAlignment(Qt::AlignCenter);
            QFont font = label->font();
            font.setPointSize(24);
            label->setFont(font);

            ui->maszyna->addWidget(label, i, j);  // ← UŻYWASZ LAYOUT Z .ui
            gridLabels[i][j] = label;
        }
    }
}

int MainWindow::PrzypiszOwocek() {
    // Zbieramy wartości prawdopodobieństw przed losowaniem
    WczytajPrawdopodobienstwa();

    // Losujemy liczbę z zakresu sumy prawdopodobieństw
    int a = rand() % sumaProporcji;

    // Przypisujemy owoc na podstawie wprowadzonych prawdopodobieństw
    if (a < p_japko) return 0;  // Japko
    if (a < p_japko + p_banan) return 1;  // Banan
    if (a < p_japko + p_banan + p_winogrono) return 2;  // Winogrono
    if (a < p_japko + p_banan + p_winogrono + p_wisnia) return 3;  // Wiśnia
    if (a < p_japko + p_banan + p_winogrono + p_wisnia + p_ananas) return 4;  // Ananas
    if (a < p_japko + p_banan + p_winogrono + p_wisnia + p_ananas + p_kiwi) return 5;  // Kiwi
    return 6;  // Bonus (domyślnie)
}
\
void MainWindow::AktualizujSaldo()
{
    ui->saldoLabel->setText(QString("%1").arg(saldo));
}

void MainWindow::SprawdzWygrana()
{
    float wygrana = 0;
    int rows = gridLabels.size();
    int cols = rows > 0 ? gridLabels[0].size() : 0;

    int SumaWystapien[7] = {0};
    QString wynikWygranej;  // String do przechowywania wyników

    // Zliczanie wystąpień symboli
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            QString tekst = gridLabels[i][j]->text();
            if (tekst == "🍎") SumaWystapien[0]++;
            if (tekst == "🍌") SumaWystapien[1]++;
            if (tekst == "🍇") SumaWystapien[2]++;
            if (tekst == "🍒") SumaWystapien[3]++;
            if (tekst == "🍍") SumaWystapien[4]++;
            if (tekst == "🥝") SumaWystapien[5]++;
            if (tekst == "🎁") SumaWystapien[6]++;
        }
    }

    // Sprawdzamy wygrane i budujemy wynik wygranej
    if (SumaWystapien[0] >= l_japko) {
        wygrana += w_japko*stawka;
        wynikWygranej += QString("🍎 %1: %2\n").arg(SumaWystapien[0]).arg(w_japko);
    }
    if (SumaWystapien[1] >= l_banan) {
        wygrana += w_banan*stawka;
        wynikWygranej += QString("🍌 %1: %2\n").arg(SumaWystapien[1]).arg(w_banan);
    }
    if (SumaWystapien[2] >= l_winogrono) {
        wygrana += w_winogrono*stawka;
        wynikWygranej += QString("🍇 %1: %2\n").arg(SumaWystapien[2]).arg(w_winogrono);
    }
    if (SumaWystapien[3] >= l_wisnia) {
        wygrana += w_wisnia*stawka;
        wynikWygranej += QString("🍒 %1: %2\n").arg(SumaWystapien[3]).arg(w_wisnia);
    }
    if (SumaWystapien[4] >= l_ananas) {
        wygrana += w_ananas*stawka;
        wynikWygranej += QString("🍍 %1: %2\n").arg(SumaWystapien[4]).arg(w_ananas);
    }
    if (SumaWystapien[5] >= l_kiwi) {
        wygrana += w_kiwi*stawka;
        wynikWygranej += QString("🥝 %1: %2\n").arg(SumaWystapien[5]).arg(w_kiwi);
    }

    // Jeśli jest wygrana, aktualizujemy saldo i wyświetlamy wynik
    if (wygrana > 0)
    {
        saldo += wygrana;  // Dodajemy wygraną do salda
        AktualizujSaldo();  // Funkcja do aktualizacji etykiety salda w UI

        // Wyświetlamy wynik wygranej w odpowiednim formacie
        ui->infoLabel->setText(QString("Wygrana: %1\n%2").arg(wygrana).arg(wynikWygranej));
    }
    else
    {
        ui->infoLabel->setText("Brak wygranej.");
    }
}




void MainWindow::LosujOdNowa()
{
    if (saldo < stawka) {
        // Jeśli saldo jest mniejsze niż stawka, to po prostu kończymy funkcję.
        ui->maszyna->setEnabled(false);  // Możesz wyłączyć maszynę albo przycisk
        return; // Zatrzymuje dalsze wykonywanie funkcji
    }

    int rows = gridLabels.size();
    int cols = rows > 0 ? gridLabels[0].size() : 0;

    // Przypisujemy wartości progów z UI
    WczytajPrawdopodobienstwa();

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            int owoc = PrzypiszOwocek();  // Używamy nowej funkcji z dynamicznymi progami
            QStringList owoce = { "🍎", "🍌", "🍇", "🍒", "🍍", "🥝", "🎁" };
            gridLabels[i][j]->setText(owoce[owoc]);
        }
    }

    if (saldo < stawka) {
        // np. zablokuj guzik albo wyświetl że nie masz na spin
        return;
    }
    saldo -= stawka;
    AktualizujSaldo();
    SprawdzWygrana();

}

void MainWindow::WczytajPrawdopodobienstwa()
{
    // Pobieramy wartości od użytkownika, jeśli pole nie jest puste
    p_japko = ui->JapkoEdit->text().isEmpty() ? 30 : ui->JapkoEdit->text().toInt();
    p_banan = ui->BananEdit->text().isEmpty() ? 20 : ui->BananEdit->text().toInt();
    p_winogrono = ui->WinogronkoEdit->text().isEmpty() ? 15 : ui->WinogronkoEdit->text().toInt();
    p_wisnia = ui->WisniaEdit->text().isEmpty() ? 13 : ui->WisniaEdit->text().toInt();
    p_ananas = ui->AnanasEdit->text().isEmpty() ? 10 : ui->AnanasEdit->text().toInt();
    p_kiwi = ui->KiwiEdit->text().isEmpty() ? 8 : ui->KiwiEdit->text().toInt();
    p_bonus = ui->BonusEdit->text().isEmpty() ? 4 : ui->BonusEdit->text().toInt();

    // Ustawiamy na 0 wszystko co ujemne
    if (p_japko < 0) p_japko = 0;
    if (p_banan < 0) p_banan = 0;
    if (p_winogrono < 0) p_winogrono = 0;
    if (p_wisnia < 0) p_wisnia = 0;
    if (p_ananas < 0) p_ananas = 0;
    if (p_kiwi < 0) p_kiwi = 0;
    if (p_bonus < 0) p_bonus = 0;

    // Jeśli wszystkie są zerowe, to ustawiamy bezpiecznie na 1
    if (p_japko == 0 && p_banan == 0 && p_winogrono == 0 &&
        p_wisnia == 0 && p_ananas == 0 && p_kiwi == 0 && p_bonus == 0)
    {
        p_japko = 1;
        p_banan = 1;
        p_winogrono = 1;
        p_wisnia = 1;
        p_ananas = 1;
        p_kiwi = 1;
        p_bonus = 1;
    }

    // Obliczamy sumę proporcji
    sumaProporcji = p_japko + p_banan + p_winogrono + p_wisnia + p_ananas + p_kiwi + p_bonus;

    // Ustawiamy te wartości z powrotem do QLineEdit, żeby było widać co naprawdę siedzi
    ui->JapkoEdit->setText(QString::number(p_japko));
    ui->BananEdit->setText(QString::number(p_banan));
    ui->WinogronkoEdit->setText(QString::number(p_winogrono));
    ui->WisniaEdit->setText(QString::number(p_wisnia));
    ui->AnanasEdit->setText(QString::number(p_ananas));
    ui->KiwiEdit->setText(QString::number(p_kiwi));
    ui->BonusEdit->setText(QString::number(p_bonus));



    l_japko = ui->liczbaSymboliLineEdit_Japko->text().isEmpty() ? 8 : ui->liczbaSymboliLineEdit_Japko->text().toInt();
    l_banan = ui->liczbaSymboliLineEdit_Banan->text().isEmpty() ? 8 : ui->liczbaSymboliLineEdit_Banan->text().toInt();
    l_winogrono = ui->liczbaSymboliLineEdit_Winogronko->text().isEmpty() ? 8 : ui->liczbaSymboliLineEdit_Winogronko->text().toInt();
    l_wisnia = ui->liczbaSymboliLineEdit_Wisnia->text().isEmpty() ? 8 : ui->liczbaSymboliLineEdit_Wisnia->text().toInt();
    l_ananas = ui->liczbaSymboliLineEdit_Ananas->text().isEmpty() ? 8 : ui->liczbaSymboliLineEdit_Ananas->text().toInt();
    l_kiwi = ui->liczbaSymboliLineEdit_Kiwi->text().isEmpty() ? 8 : ui->liczbaSymboliLineEdit_Kiwi->text().toInt();
    l_bonus = ui->liczbaSymboliLineEdit_Bonus->text().isEmpty() ? 4 : ui->liczbaSymboliLineEdit_Bonus->text().toInt();


    w_japko = ui->kwotaWygranejLineEdit_Japko->text().isEmpty() ? 0.75 : ui->kwotaWygranejLineEdit_Japko->text().toFloat();
    w_banan = ui->kwotaWygranejLineEdit_Banan->text().isEmpty() ? 1.25 : ui->kwotaWygranejLineEdit_Banan->text().toFloat();
    w_winogrono = ui->kwotaWygranejLineEdit_Winogronko->text().isEmpty() ? 2.0 : ui->kwotaWygranejLineEdit_Winogronko->text().toFloat();
    w_wisnia = ui->kwotaWygranejLineEdit_Wisnia->text().isEmpty() ? 3.0 : ui->kwotaWygranejLineEdit_Wisnia->text().toFloat();
    w_ananas = ui->kwotaWygranejLineEdit_Ananas->text().isEmpty() ? 5.0 : ui->kwotaWygranejLineEdit_Ananas->text().toFloat();
    w_kiwi = ui->kwotaWygranejLineEdit_Kiwi->text().isEmpty() ? 8.0 : ui->kwotaWygranejLineEdit_Kiwi->text().toFloat();
}

void MainWindow::ZwiekszStawke() {
    if (stawka + 1 <= saldo) {
        stawka++;
        ui->StawkaLabel->setText(QString("%1").arg(stawka));
    }
}

void MainWindow::ZmniejszStawke() {
    if (stawka > 1) {
        stawka--;
        ui->StawkaLabel->setText(QString("%1").arg(stawka));
    }
}







