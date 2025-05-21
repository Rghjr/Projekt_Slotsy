#include "oknogra1.h"
#include "ui_oknogra1.h"
#include "gra1mechaniki.h"
#include <QFont>
#include <QThread>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QTimer>


OknoGra1::OknoGra1(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::OknoGra1)
    , mechanika(new Gra1Mechaniki)
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

    ui->liczbaSymboliLineEdit_Japko->setText("8");      // Tu ustawiłeś liczbę symboli dla jabłka
    ui->liczbaSymboliLineEdit_Banan->setText("8");      // Liczba symboli dla banana
    ui->liczbaSymboliLineEdit_Winogronko->setText("8"); // Liczba symboli dla winogronka
    ui->liczbaSymboliLineEdit_Wisnia->setText("8");     // Liczba symboli dla wiśni
    ui->liczbaSymboliLineEdit_Ananas->setText("8");     // Liczba symboli dla ananasa
    ui->liczbaSymboliLineEdit_Kiwi->setText("8");       // Liczba symboli dla kiwi
    ui->liczbaSymboliLineEdit_Bonus->setText("4");      // Liczba symboli dla bonusu

    // Ustawienie początkowych wartości wygranych (jeśli też chcesz je ustawić na etykietach)
    ui->kwotaWygranejLineEdit_Japko->setText("0.75");   // Kwota wygranej dla jabłka
    ui->kwotaWygranejLineEdit_Banan->setText("1.25");   // Kwota wygranej dla banana
    ui->kwotaWygranejLineEdit_Winogronko->setText("2"); // Kwota wygranej dla winogronka
    ui->kwotaWygranejLineEdit_Wisnia->setText("3");     // Kwota wygranej dla wiśni
    ui->kwotaWygranejLineEdit_Ananas->setText("5");     // Kwota wygranej dla ananasa
    ui->kwotaWygranejLineEdit_Kiwi->setText("8");       // Kwota wygranej dla kiwi

    ui->liczbaFreeSpinowLineEdit->setText("10");
    ui->liczbaDodatkowychSpinowLineEdit->setText("1");

    // Ładowanie prawdopodobieństw (już z początkowymi wartościami)
    WczytajPrawdopodobienstwa();

    // Połączenie przycisku z funkcją
    connect(ui->SPINPRZYCISK, &QPushButton::clicked, this, &OknoGra1::LosujOdNowa);

    ui->AUTOSPINPRZYCISK->setCheckable(true);
    connect(ui->AUTOSPINPRZYCISK, &QPushButton::toggled, this, &OknoGra1::Autospin);

    ui->StawkaLabel->setText("Stawka: 5");
    connect(ui->plusButton, &QPushButton::clicked, this, &OknoGra1::ZwiekszStawke);
    connect(ui->minusButton, &QPushButton::clicked, this, &OknoGra1::ZmniejszStawke);
}



OknoGra1::~OknoGra1()
{
    delete ui;
}



void OknoGra1::UstawGrid(QVector<QVector<int>> tablica, int rows, int cols)
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

void OknoGra1::AktualizujSaldo()
{
    ui->saldoLabel->setText(QString("Aktualne saldo: %1").arg(saldo));
}

bool bonus=false;


void OknoGra1::SprawdzWygrana() {
    // 📉 Odejmujemy stawkę od salda gracza
    saldo -= stawka;
    AktualizujSaldo();

    QVector<QVector<QString>> siatkaTekstow; // konwersja Qlabel na QString
    for (const auto& row : gridLabels) {
        QVector<QString> teksty;
        for (const auto& label : row) {
            teksty.append(label->text()); // Pobieramy tekst z QLabel
        }
        siatkaTekstow.append(teksty);
    }

    // 🔄 Pobieramy wynik wygranej z mechaniki gry
    QMap<QString, QPair<int, float>> wynikWygranej = mechanika->SprawdzWygranaMechanika(siatkaTekstow, stawka);
    float wygrana = 0;

    // 📊 Sumujemy całkowitą wartość wygranej
    for (const auto& wartosc : wynikWygranej.values()) {
        wygrana += wartosc.second;
    }

    // 🎁 Sprawdzamy, czy gracz zdobył bonus
    QString bonusInfo;
    if (wynikWygranej.contains("🎁")) {
        bonusInfo = "🎁 BONUS 🎁\n";
        Bonus();
    }

    // 🏆 Aktualizacja UI na podstawie wyniku gry
    if (wygrana > 0) {
        saldo += wygrana;
        AktualizujSaldo();

        // 📜 Tworzymy szczegóły wygranej
        QString szczegolyWygranej;
        for (auto it = wynikWygranej.begin(); it != wynikWygranej.end(); ++it) {
            szczegolyWygranej += QString("%1x %2 : %3\n").arg(it.value().first).arg(it.key()).arg(it.value().second);
        }

        ui->infoLabel->setText(bonusInfo + QString("Wygrana: %1\n%2").arg(wygrana).arg(szczegolyWygranej));
    } else {
        ui->infoLabel->setText(bonusInfo + "Brak wygranej");
    }
}



void OknoGra1::Bonus() {
    bonus = true; // Aktywujemy tryb bonusowy
    int l_freespin = mechanika->PobierzLiczbeFreeSpinow();
    int l_dodatkowychFreeSpinow = mechanika->PobierzLiczbeDodatkowychFreeSpinow();

    QVector<QVector<QString>> siatkaTekstow; // konwersja Qlabel na QString
    for (const auto& row : gridLabels) {
        QVector<QString> teksty;
        for (const auto& label : row) {
            teksty.append(label->text()); // Pobieramy tekst z QLabel
        }
        siatkaTekstow.append(teksty);
    }

    ui->liczbaFreeSpinow->setText(QString("FreeSpiny: %1").arg(l_freespin)); // Aktualizacja UI dla free spinów

    // Wywołujemy mechanikę gry, aby sprawdzić bonusowe spiny
    QMap<QString, QPair<int, float>> wynikWygranej = mechanika->BonusMechanika(siatkaTekstow, l_freespin, l_dodatkowychFreeSpinow, stawka);

    // Pobieramy całkowitą wartość wygranej z mechaniki gry
    float sumaWygranychLacznie = wynikWygranej["TOTAL"].second;

    // Jeśli gracz wygrał, aktualizujemy saldo i interfejs
    if (sumaWygranychLacznie > 0) {
        saldo += sumaWygranychLacznie;
        AktualizujSaldo(); // Aktualizacja widżetu salda

        // Tworzymy szczegóły wygranej dla UI
        QString szczegolyWygranej;
        for (auto it = wynikWygranej.begin(); it != wynikWygranej.end(); ++it) {
            if (it.key() != "TOTAL") szczegolyWygranej += QString("%1x %2 : %3\n").arg(it.value().first).arg(it.key()).arg(it.value().second);
        }

        ui->infoLabel->setText(QString("Wygrana: %1\n%2").arg(sumaWygranychLacznie).arg(szczegolyWygranej)); // Wyświetlenie wyniku
    } else {
        ui->infoLabel->setText("Brak wygranej"); // Jeśli nie było wygranej, informujemy gracza
    }

    bonus = false; // Wyłączamy tryb bonusowy po zakończeniu
}




void OknoGra1::LosujOdNowa()
{
    if (saldo < stawka) {
        ui->maszyna->setEnabled(false);
        return;
    }

    ui->SPINPRZYCISK->setEnabled(false);
    int rows = gridLabels.size();
    int cols = rows > 0 ? gridLabels[0].size() : 0;

    WczytajPrawdopodobienstwa();
    QStringList owoce = {"🍎", "🍌", "🍇", "🍒", "🍍", "🥝", "🎁"};

    int i = rows - 1;
    int j = 0;

    while (j < cols) {
        int owoc = mechanika->PrzypiszOwocek();
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

    if (bonus==false) SprawdzWygrana();
    ui->SPINPRZYCISK->setEnabled(true);
}



void OknoGra1::Autospin(bool checked)
{
    if (checked)
    {
        if (!autoSpinTimer) {
            autoSpinTimer = new QTimer(this);
            connect(autoSpinTimer, &QTimer::timeout, this, &OknoGra1::LosujOdNowa);
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




void OknoGra1::UsunPolaczoneOwoce(QString a)
{
    const QStringList owoce = {"🍎", "🍌", "🍇", "🍒", "🍍", "🥝", "🎁"};
    const int rows = gridLabels.size();
    const int cols = rows > 0 ? gridLabels[0].size() : 0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            QLabel* label = gridLabels[i][j];
            if (label->text() == a) {
                int x = mechanika->PrzypiszOwocek();
                if (x >= 0 && x < owoce.size()) {
                    label->setText(owoce[x]);
                }
            }
        }
    }
}



void OknoGra1::WczytajPrawdopodobienstwa()
{
    // Pobieramy wartości od użytkownika, jeśli pole nie jest puste
    int japko = ui->JapkoEdit->text().isEmpty() ? 30 : ui->JapkoEdit->text().toInt();
    int banan = ui->BananEdit->text().isEmpty() ? 20 : ui->BananEdit->text().toInt();
    int winogrono = ui->WinogronkoEdit->text().isEmpty() ? 15 : ui->WinogronkoEdit->text().toInt();
    int wisnia = ui->WisniaEdit->text().isEmpty() ? 13 : ui->WisniaEdit->text().toInt();
    int ananas = ui->AnanasEdit->text().isEmpty() ? 10 : ui->AnanasEdit->text().toInt();
    int kiwi = ui->KiwiEdit->text().isEmpty() ? 8 : ui->KiwiEdit->text().toInt();
    int bonus = ui->BonusEdit->text().isEmpty() ? 4 : ui->BonusEdit->text().toInt();

    // Pobieramy liczbę darmowych spinów
    int freeSpiny = ui->liczbaFreeSpinowLineEdit->text().isEmpty() ? 10 : ui->liczbaFreeSpinowLineEdit->text().toInt();
    int dodatkoweSpiny = ui->liczbaDodatkowychSpinowLineEdit->text().isEmpty() ? 1 : ui->liczbaDodatkowychSpinowLineEdit->text().toInt();

    // Pobieramy minimalne liczby symboli do wygranej
    int lJapko = ui->liczbaSymboliLineEdit_Japko->text().isEmpty() ? 8 : ui->liczbaSymboliLineEdit_Japko->text().toInt();
    int lBanan = ui->liczbaSymboliLineEdit_Banan->text().isEmpty() ? 8 : ui->liczbaSymboliLineEdit_Banan->text().toInt();
    int lWinogrono = ui->liczbaSymboliLineEdit_Winogronko->text().isEmpty() ? 8 : ui->liczbaSymboliLineEdit_Winogronko->text().toInt();
    int lWisnia = ui->liczbaSymboliLineEdit_Wisnia->text().isEmpty() ? 8 : ui->liczbaSymboliLineEdit_Wisnia->text().toInt();
    int lAnanas = ui->liczbaSymboliLineEdit_Ananas->text().isEmpty() ? 8 : ui->liczbaSymboliLineEdit_Ananas->text().toInt();
    int lKiwi = ui->liczbaSymboliLineEdit_Kiwi->text().isEmpty() ? 8 : ui->liczbaSymboliLineEdit_Kiwi->text().toInt();
    int lBonus = ui->liczbaSymboliLineEdit_Bonus->text().isEmpty() ? 4 : ui->liczbaSymboliLineEdit_Bonus->text().toInt();

    // Pobieramy wartości wygranej
    float wJapko = ui->kwotaWygranejLineEdit_Japko->text().isEmpty() ? 0.75 : ui->kwotaWygranejLineEdit_Japko->text().toFloat();
    float wBanan = ui->kwotaWygranejLineEdit_Banan->text().isEmpty() ? 1.25 : ui->kwotaWygranejLineEdit_Banan->text().toFloat();
    float wWinogrono = ui->kwotaWygranejLineEdit_Winogronko->text().isEmpty() ? 2.0 : ui->kwotaWygranejLineEdit_Winogronko->text().toFloat();
    float wWisnia = ui->kwotaWygranejLineEdit_Wisnia->text().isEmpty() ? 3.0 : ui->kwotaWygranejLineEdit_Wisnia->text().toFloat();
    float wAnanas = ui->kwotaWygranejLineEdit_Ananas->text().isEmpty() ? 5.0 : ui->kwotaWygranejLineEdit_Ananas->text().toFloat();
    float wKiwi = ui->kwotaWygranejLineEdit_Kiwi->text().isEmpty() ? 8.0 : ui->kwotaWygranejLineEdit_Kiwi->text().toFloat();

    // Przekazujemy wartości do mechaniki gry
    mechanika->UstawPrawdopodobienstwa(japko, banan, winogrono, wisnia, ananas, kiwi, bonus,
                                       lJapko, lBanan, lWinogrono, lWisnia, lAnanas, lKiwi, lBonus,
                                       wJapko, wBanan, wWinogrono, wWisnia, wAnanas, wKiwi,
                                       freeSpiny, dodatkoweSpiny);

    // Obliczamy sumę proporcji
    sumaProporcji = mechanika->PobierzSumaProporcji();
}



void OknoGra1::ZwiekszStawke()
{
    if (stawka + 1 <= saldo) {
        stawka++;
        ui->StawkaLabel->setText(QString("Stawka: %1").arg(stawka));
    }
}



void OknoGra1::ZmniejszStawke()
{
    if (stawka > 1) {
        stawka--;
        ui->StawkaLabel->setText(QString("Stawka: %1").arg(stawka));
    }
}
