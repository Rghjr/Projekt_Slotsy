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

    // Ładowanie prawdopodobieństw (już z początkowymi wartościami)
    WczytajPrawdopodobienstwa();

    // Połączenie przycisku z funkcją
    connect(ui->SPINPRZYCISK, &QPushButton::clicked, this, &MainWindow::LosujOdNowa);
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


void MainWindow::LosujOdNowa()
{
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

}




