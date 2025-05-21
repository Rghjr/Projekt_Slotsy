#include "oknogra2.h"
#include "ui_oknogra2.h"
#include <QFont>
#include <QThread>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QTimer>

OknoGra2::OknoGra2(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::OknoGra2)
{
    ui->setupUi(this);
    connect(ui->SPINPRZYCISK, &QPushButton::clicked, this, &OknoGra2::LosujOdNowa);

    ui->l_1_check->setChecked(true);
    ui->l_2_check->setChecked(true);
    ui->l_3_check->setChecked(true);
    ui->l_4_check->setChecked(true);
    ui->l_5_check->setChecked(true);

    ui->AUTOSPINPRZYCISK->setCheckable(true);
    connect(ui->AUTOSPINPRZYCISK, &QPushButton::toggled, this, &OknoGra2::Autospin);
}

OknoGra2::~OknoGra2()
{
    delete ui;
}

void OknoGra2::UstawGrid(int **tablica, int rows, int cols)
{
    QStringList owoce = {"🍎", "🍌", "🍇", "🍒", "🍍", "🥝", "🎁"};

    // wyczyść poprzednie widgety z layoutu
    QLayoutItem *item;
    while ((item = ui->maszyna->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    gridLabels.resize(rows);
    for (int i = 0; i < rows; ++i) {
        gridLabels[i].resize(cols);
        for (int j = 0; j < cols; ++j) {
            int wartosc = tablica[i][j];
            QLabel *label = new QLabel(owoce[wartosc]);
            label->setAlignment(Qt::AlignCenter);
            QFont font = label->font();
            font.setPointSize(24);
            label->setFont(font);

            ui->maszyna->addWidget(label, i, j); // ← UŻYWASZ LAYOUT Z .ui
            gridLabels[i][j] = label;
        }
    }
}

int OknoGra2::PrzypiszOwocek()
{

    // Zbieramy wartości prawdopodobieństw przed losowaniem
    WczytajPrawdopodobienstwa();

    // Losujemy liczbę z zakresu sumy prawdopodobieństw
    int a = rand() % sumaProporcji;

    // Przypisujemy owoc na podstawie wprowadzonych prawdopodobieństw

    if (a < p_japko)
        return 0; // Japko
    if (a < p_japko + p_banan)
        return 1; // Banan
    if (a < p_japko + p_banan + p_winogrono)
        return 2; // Winogrono
    if (a < p_japko + p_banan + p_winogrono + p_wisnia)
        return 3; // Wiśnia
    return 4;     // Bonus (domyślnie)

}


void OknoGra2::LosujOdNowa()
{
    if (saldo < stawka) {
        ui->maszyna->setEnabled(false);
        return;
    }

    ui->SPINPRZYCISK->setEnabled(false);
    int rows = gridLabels.size();
    int cols = rows > 0 ? gridLabels[0].size() : 0;

    WczytajPrawdopodobienstwa();
    QStringList owoce = {"🍎", "🍌", "🍇", "🍒", "🎁"};

    int i = rows - 1;
    int j = 0;

    while (j < cols) {
        int owoc = PrzypiszOwocek();
        QLabel *label = gridLabels[i][j];
        QString nowyTekst = owoce[owoc];

        if (label) {
            // Animacja
            auto *efekt = new QGraphicsOpacityEffect(label);
            label->setGraphicsEffect(efekt);

            QPropertyAnimation *zanik = new QPropertyAnimation(efekt, "opacity");
            zanik->setDuration(150);
            zanik->setStartValue(0.0);
            zanik->setEndValue(1.0);

            label->setText(nowyTekst);
            zanik->start(QAbstractAnimation::DeleteWhenStopped);
        }

        QCoreApplication::processEvents();
        QThread::msleep(40);

        // Następny element
        if (--i < 0) {
            i = rows - 1;
            ++j;
        }
    }

    ui->SPINPRZYCISK->setEnabled(true);
    SprawdzWygrana();
}

void OknoGra2::Autospin(bool checked)
{
    if (checked)
    {
        if (!autoSpinTimer) {
            autoSpinTimer = new QTimer(this);
            connect(autoSpinTimer, &QTimer::timeout, this, &OknoGra2::LosujOdNowa);
        }
        LosujOdNowa();
        autoSpinTimer->start(2000);
    }
    else
    {
        if (autoSpinTimer) {
            autoSpinTimer->stop();
        }
    }
}



void OknoGra2::WczytajPrawdopodobienstwa()
{
    // Pobieramy wartości od użytkownika, jeśli pole nie jest puste
    p_japko = ui->JapkoEdit->text().isEmpty() ? 30 : ui->JapkoEdit->text().toInt();
    p_banan = ui->BananEdit->text().isEmpty() ? 25 : ui->BananEdit->text().toInt();
    p_winogrono = ui->WinogronkoEdit->text().isEmpty() ? 20 : ui->WinogronkoEdit->text().toInt();
    p_wisnia = ui->WisniaEdit->text().isEmpty() ? 15 : ui->WisniaEdit->text().toInt();
    p_bonus = ui->BonusEdit->text().isEmpty() ? 10 : ui->BonusEdit->text().toInt();

    // Ustawiamy na 0 wszystko co ujemne
    if (p_japko < 0)
        p_japko = 0;
    if (p_banan < 0)
        p_banan = 0;
    if (p_winogrono < 0)
        p_winogrono = 0;
    if (p_wisnia < 0)
        p_wisnia = 0;
    if (p_bonus < 0)
        p_bonus = 0;

    // Jeśli wszystkie są zerowe, to ustawiamy bezpiecznie na 1
    if (p_japko == 0 && p_banan == 0 && p_winogrono == 0 && p_wisnia == 0 && p_bonus == 0) {
        p_japko = 1;
        p_banan = 1;
        p_winogrono = 1;
        p_wisnia = 1;
        p_bonus = 1;
    }

    // Obliczamy sumę proporcji
    sumaProporcji = p_japko + p_banan + p_winogrono + p_wisnia + p_bonus;

    // Ustawiamy te wartości z powrotem do QLineEdit, żeby było widać co naprawdę siedzi
    ui->JapkoEdit->setText(QString::number(p_japko));
    ui->BananEdit->setText(QString::number(p_banan));
    ui->WinogronkoEdit->setText(QString::number(p_winogrono));
    ui->WisniaEdit->setText(QString::number(p_wisnia));
    ui->BonusEdit->setText(QString::number(p_bonus));



    w_japko = ui->kwotaWygranejLineEdit_Japko->text().isEmpty()
                  ? 0.75
                  : ui->kwotaWygranejLineEdit_Japko->text().toFloat();
    w_banan = ui->kwotaWygranejLineEdit_Banan_->text().isEmpty()
                  ? 1.25
                  : ui->kwotaWygranejLineEdit_Banan_->text().toFloat();
    w_winogrono = ui->kwotaWygranejLineEdit_Winogronko_->text().isEmpty()
                      ? 2.0
                      : ui->kwotaWygranejLineEdit_Winogronko_->text().toFloat();
    w_wisnia = ui->kwotaWygranejLineEdit_Wisnia->text().isEmpty()
                   ? 3.0
                   : ui->kwotaWygranejLineEdit_Wisnia->text().toFloat();
    w_bonus = ui->kwotaWygranejLineEdit_Bonus->text().isEmpty()
                   ? 5.0
                   : ui->kwotaWygranejLineEdit_Bonus->text().toFloat();
    mn_bonus = ui->mnoznikBonusuLineEdit->text().isEmpty()
                   ? 10.0
                   : ui->mnoznikBonusuLineEdit->text().toFloat();



    ui->kwotaWygranejLineEdit_Japko->setText(QString::number(w_japko));
    ui->kwotaWygranejLineEdit_Banan_->setText(QString::number(w_banan));
    ui->kwotaWygranejLineEdit_Winogronko_->setText(QString::number(w_winogrono));
    ui->kwotaWygranejLineEdit_Wisnia->setText(QString::number(w_wisnia));
    ui->kwotaWygranejLineEdit_Bonus->setText(QString::number(w_bonus));

    ui->mnoznikBonusuLineEdit->setText(QString::number(mn_bonus));

    l1 = ui->l_1_check->isChecked();
    l2 = ui->l_2_check->isChecked();
    l3 = ui->l_3_check->isChecked();
    l4 = ui->l_4_check->isChecked();
    l5 = ui->l_5_check->isChecked();
    l6 = ui->l_6_check->isChecked();
    l7 = ui->l_7_check->isChecked();
    l8 = ui->l_8_check->isChecked();
    l9 = ui->l_9_check->isChecked();
    l10 = ui->l_10_check->isChecked();
    l11 = ui->l_11_check->isChecked();
    l12 = ui->l_12_check->isChecked();
    l13 = ui->l_13_check->isChecked();
    l14 = ui->l_14_check->isChecked();
    l15 = ui->l_15_check->isChecked();
    l16 = ui->l_16_check->isChecked();
    l17 = ui->l_17_check->isChecked();
}

void OknoGra2::SprawdzWygrana()
{
    saldo -= stawka;
    AktualizujSaldo();
    WczytajPrawdopodobienstwa();

    ui->WygraneLabel->clear();
    float wygrana = 0;
    int bonusCount = 0;
    bool anyWin = false;
    int rows = gridLabels.size();
    int cols = rows > 0 ? gridLabels[0].size() : 0;

    /// 🍎🍌🍇🍒🎁

    QString a00 = gridLabels[0][0]->text();     /// lewa góra
    QString a01 = gridLabels[0][1]->text();     /// środek góra
    QString a02 = gridLabels[0][2]->text();     /// prawo góra

    QString a10 = gridLabels[1][0]->text();     /// lewo środek
    QString a11 = gridLabels[1][1]->text();     /// środek środek
    QString a12 = gridLabels[1][2]->text();     /// prawo środek

    QString a20 = gridLabels[2][0]->text();     /// lewo dół
    QString a21 = gridLabels[2][1]->text();     /// środek dół
    QString a22 = gridLabels[2][2]->text();     /// prawo dół


    // 1, 2, 3 - linie proste od lewej do prawej
    if (l1 && a00 == a01 && a01 == a02) { wygrana += Winek(1); anyWin = true; if (a00 == "🎁") bonusCount++; }
    if (l2 && a10 == a11 && a11 == a12) { wygrana += Winek(2); anyWin = true; if (a10 == "🎁") bonusCount++; }
    if (l3 && a20 == a21 && a21 == a22) { wygrana += Winek(3); anyWin = true; if (a20 == "🎁") bonusCount++; }

    // 4 i 5 - ukośne
    if (l4 && a00 == a11 && a11 == a22) { wygrana += Winek(4); anyWin = true; if (a00 == "🎁") bonusCount++; }
    if (l5 && a20 == a11 && a11 == a02) { wygrana += Winek(5); anyWin = true; if (a20 == "🎁") bonusCount++; }

    // 6 i 7
    if (l6 && a20 == a11 && a11 == a22) { wygrana += Winek(6); anyWin = true; if (a20 == "🎁") bonusCount++; }
    if (l7 && a10 == a01 && a01 == a12) { wygrana += Winek(7); anyWin = true; if (a10 == "🎁") bonusCount++; }

    // 8 i 9
    if (l8 && a00 == a11 && a11 == a02) { wygrana += Winek(8); anyWin = true; if (a00 == "🎁") bonusCount++; }
    if (l9 && a10 == a21 && a21 == a12) { wygrana += Winek(9); anyWin = true; if (a10 == "🎁") bonusCount++; }

    // 10 i 11
    if (l10 && a20 == a21 && a21 == a12) { wygrana += Winek(10); anyWin = true; if (a20 == "🎁") bonusCount++; }
    if (l11 && a10 == a11 && a11 == a02) { wygrana += Winek(11); anyWin = true; if (a10 == "🎁") bonusCount++; }

    // 12 i 13
    if (l12 && a00 == a01 && a01 == a12) { wygrana += Winek(12); anyWin = true; if (a00 == "🎁") bonusCount++; }
    if (l13 && a10 == a11 && a11 == a22) { wygrana += Winek(13); anyWin = true; if (a10 == "🎁") bonusCount++; }

    // 14 i 15
    if (l14 && a10 == a01 && a01 == a02) { wygrana += Winek(14); anyWin = true; if (a10 == "🎁") bonusCount++; }
    if (l15 && a20 == a11 && a11 == a12) { wygrana += Winek(15); anyWin = true; if (a20 == "🎁") bonusCount++; }

    // 16 i 17
    if (l16 && a00 == a11 && a11 == a12) { wygrana += Winek(16); anyWin = true; if (a00 == "🎁") bonusCount++; }
    if (l17 && a10 == a11 && a11 == a02) { wygrana += Winek(17); anyWin = true; if (a10 == "🎁") bonusCount++; }


    QString wynikTekst = QString("Łączna wygrana: %1\n").arg(wygrana);
    ui->LacznaWygrana_Label->setText(wynikTekst);

    saldo += wygrana;
    AktualizujSaldo();
}

float OknoGra2::Winek(int x)
{
    // Wskaźnik na wiersz pierwszej kolumny, zależnie od linii
    int row = 0;
    if (x == 1 || x == 4 || x == 8 || x == 12 || x == 16) row = 0;
    else if (x == 2 || x == 7 || x == 9 || x == 11 || x == 13 || x == 14 || x == 17) row = 1;
    else if (x == 3 || x == 5 || x == 6 || x == 10 || x == 15) row = 2;
    else return 0; // Nieznana linia?

    QString znak = gridLabels[row][0]->text();

    // Mapka symbol → współczynnik
    static const QMap<QString, float> wspMap {
        {"🍎", w_japko},
        {"🍌", w_banan},
        {"🍇", w_winogrono},
        {"🍒", w_wisnia},
        {"🎁", w_bonus}
    };

    float wsp = wspMap.value(znak, 0.0f);

    float wygrana = stawka * wsp;

    QString currentText = ui->WygraneLabel->text();
    currentText += QString("\nLinia %1: %2 - wygrana: %3").arg(x).arg(znak).arg(wygrana);

    ui->WygraneLabel->setText(currentText);

    return wygrana;
}




void OknoGra2::AktualizujSaldo()
{
    ui->saldoLabel->setText(QString("Saldo: %1").arg(saldo));
}
