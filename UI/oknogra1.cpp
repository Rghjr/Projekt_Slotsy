#include "oknogra1.h"
#include "ui_oknogra1.h"
#include <QFont>
#include <QThread>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "wygrane.h"


OknoGra1::OknoGra1(OknoStartowe* startoweOkno, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::OknoGra1)
    , oknoStartowe(startoweOkno)
{
    ui->setupUi(this);

    connect(ui->powrotButton, &QPushButton::clicked, this, &OknoGra1::on_returnButton_select);

    connect(ui->SPINPRZYCISK, &QPushButton::clicked, this, &OknoGra1::LosujOdNowa);

    ui->AUTOSPINPRZYCISK->setCheckable(true);
    connect(ui->AUTOSPINPRZYCISK, &QPushButton::toggled, this, &OknoGra1::Autospin);

    ui->StawkaLabel->setText("Stawka: 5");
    connect(ui->plusButton, &QPushButton::clicked, this, &OknoGra1::ZwiekszStawke);
    connect(ui->minusButton, &QPushButton::clicked, this, &OknoGra1::ZmniejszStawke);

    saldo = oknoStartowe->pobierzSaldo();
    ui->saldoLabel->setText(QString("Saldo: %1").arg(QString::number(saldo, 'f', 2)));

    bonus = false;
    freespiny = 0;


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

    if(WczytanieZPliku())
    {
        ui->JapkoEdit->setText(QString::number(p_japko));
        ui->BananEdit->setText(QString::number(p_banan));
        ui->WinogronkoEdit->setText(QString::number(p_winogrono));
        ui->WisniaEdit->setText(QString::number(p_wisnia));
        ui->AnanasEdit->setText(QString::number(p_ananas));
        ui->KiwiEdit->setText(QString::number(p_kiwi));
        ui->BonusEdit->setText(QString::number(p_bonus));


        ui->liczbaSymboliLineEdit_Japko->setText(QString::number(l_japko));
        ui->liczbaSymboliLineEdit_Banan->setText(QString::number(l_banan));
        ui->liczbaSymboliLineEdit_Winogronko->setText(QString::number(l_winogrono));
        ui->liczbaSymboliLineEdit_Wisnia->setText(QString::number(l_wisnia));
        ui->liczbaSymboliLineEdit_Ananas->setText(QString::number(l_ananas));
        ui->liczbaSymboliLineEdit_Kiwi->setText(QString::number(l_kiwi));
        ui->liczbaSymboliLineEdit_Bonus->setText(QString::number(l_bonus));


        ui->kwotaWygranejLineEdit_Japko->setText(QString::number(w_japko));
        ui->kwotaWygranejLineEdit_Banan->setText(QString::number(w_banan));
        ui->kwotaWygranejLineEdit_Winogronko->setText(QString::number(w_winogrono));
        ui->kwotaWygranejLineEdit_Wisnia->setText(QString::number(w_wisnia));
        ui->kwotaWygranejLineEdit_Ananas->setText(QString::number(w_ananas));
        ui->kwotaWygranejLineEdit_Kiwi->setText(QString::number(w_kiwi));


        ui->liczbaFreeSpinowLineEdit->setText(QString::number(l_freespin));
        ui->liczbaDodatkowychSpinowLineEdit->setText(QString::number(l_dodatkowychFreeSpinow));
    }

    WczytajPrawdopodobienstwa();
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

int OknoGra1::PrzypiszOwocek()
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
    if (a < p_japko + p_banan + p_winogrono + p_wisnia + p_ananas)
        return 4; // Ananas
    if (a < p_japko + p_banan + p_winogrono + p_wisnia + p_ananas + p_kiwi)
        return 5; // Kiwi
    return 6;     // Bonus (domyślnie)
}

void OknoGra1::AktualizujSaldo()
{
    oknoStartowe->ustawSaldo(saldo);
    ui->saldoLabel->setText(QString("Saldo: %1").arg(QString::number(saldo, 'f', 2)));
}

void OknoGra1::SprawdzWygrana()
{
    QMap<QString, QPair<int, float>> wynikWygranej; // <symbol, <ilość trafień, suma wygranej>>
    saldo -= stawka;
    AktualizujSaldo();
    float wygrana = 0;
    int rows = gridLabels.size();
    int cols = rows > 0 ? gridLabels[0].size() : 0;

    int SumaWystapien[7] = {0}; // 🍎🍌🍇🍒🍍🥝🎁

    // Zliczanie wystąpień symboli
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
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

    // Sprawdzanie i zapis wygranych
    auto dodajWygrana = [&](QString symbol, int liczba, float wartosc) {
        float nagroda = wartosc * stawka;
        wygrana += nagroda;
        wynikWygranej[symbol] = qMakePair(liczba, nagroda);
    };

    if (SumaWystapien[0] >= l_japko)
        dodajWygrana("🍎", SumaWystapien[0], w_japko);
    if (SumaWystapien[1] >= l_banan)
        dodajWygrana("🍌", SumaWystapien[1], w_banan);
    if (SumaWystapien[2] >= l_winogrono)
        dodajWygrana("🍇", SumaWystapien[2], w_winogrono);
    if (SumaWystapien[3] >= l_wisnia)
        dodajWygrana("🍒", SumaWystapien[3], w_wisnia);
    if (SumaWystapien[4] >= l_ananas)
        dodajWygrana("🍍", SumaWystapien[4], w_ananas);
    if (SumaWystapien[5] >= l_kiwi)
        dodajWygrana("🥝", SumaWystapien[5], w_kiwi);

    QString bonusInfo;
    if (SumaWystapien[6] >= l_bonus)
        bonusInfo = "🎁 BONUS 🎁\n";

    // Główna część informacji o wygranej
    if (wygrana > 0) {
        saldo += wygrana;
        if (saldo < 0) saldo = 0;



        QString szczegolyWygranej;
        Wygrane zapisywacz; // Tworzymy obiekt klasy Wygrane
        for (auto it = wynikWygranej.begin(); it != wynikWygranej.end(); ++it) {
            // Budujemy string do UI
            szczegolyWygranej += QString("%1x %2 : %3\n")
                                     .arg(it.value().first)
                                     .arg(it.key())
                                     .arg(it.value().second);

            // Korzystamy z metody zapisz (dopisuje linie do pliku)
            zapisywacz.zapisz1(it.value().second, it.key(), it.value().first);
        }




        ui->infoLabel->setText(bonusInfo + QString("Wygrana: %1\n%2").arg(wygrana).arg(szczegolyWygranej));
    } else {
        ui->infoLabel->setText(bonusInfo + "Brak wygranej");
    }

    AktualizujSaldo();

    if (SumaWystapien[6] >= l_bonus) Bonus();
}

void OknoGra1::Bonus()
{
    bonus = true;
    bool czywygrane = true;
    float sumaWygranychLacznie = 0;
    WczytajPrawdopodobienstwa();
    freespiny = l_freespin;

    while (freespiny > 0)
    {
        QMap<QString, QPair<int, float>> wynikWygranej;
        bool zmianawygranej = false;
        ui->liczbaFreeSpinow->setText(QString("FreeSpiny: %1").arg(freespiny));
        freespiny--;
        LosujOdNowa();
        int sumabonusów = 0;

        do
        {
            sumabonusów = 0;
            czywygrane = false;
            float wygrana = 0;
            int rows = gridLabels.size();
            int cols = rows > 0 ? gridLabels[0].size() : 0;

            int SumaWystapien[7] = {0};

            // Zliczanie wystąpień symboli
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    QString tekst = gridLabels[i][j]->text();
                    if (tekst == "🍎") SumaWystapien[0]++;
                    if (tekst == "🍌") SumaWystapien[1]++;
                    if (tekst == "🍇") SumaWystapien[2]++;
                    if (tekst == "🍒") SumaWystapien[3]++;
                    if (tekst == "🍍") SumaWystapien[4]++;
                    if (tekst == "🥝") SumaWystapien[5]++;
                    if (tekst == "🎁") sumabonusów++;
                }
            }

            // Sprawdzamy wygrane i zapisujemy wynik
            auto dodajWygrana = [&](QString symbol, int liczba, float wartosc) {
                float nagroda = wartosc * stawka;
                wygrana += nagroda;
                if (!wynikWygranej.contains(symbol))
                    wynikWygranej[symbol] = qMakePair(1, nagroda);
                else {
                    wynikWygranej[symbol].first += 1;
                    wynikWygranej[symbol].second += nagroda;
                }
                UsunPolaczoneOwoce(symbol);
                czywygrane = true;
            };

            if (SumaWystapien[0] >= l_japko) dodajWygrana("🍎", SumaWystapien[0], w_japko);
            if (SumaWystapien[1] >= l_banan) dodajWygrana("🍌", SumaWystapien[1], w_banan);
            if (SumaWystapien[2] >= l_winogrono) dodajWygrana("🍇", SumaWystapien[2], w_winogrono);
            if (SumaWystapien[3] >= l_wisnia) dodajWygrana("🍒", SumaWystapien[3], w_wisnia);
            if (SumaWystapien[4] >= l_ananas) dodajWygrana("🍍", SumaWystapien[4], w_ananas);
            if (SumaWystapien[5] >= l_kiwi) dodajWygrana("🥝", SumaWystapien[5], w_kiwi);

            // Jeśli coś wygrało – aktualizacja UI
            if (czywygrane)
            {
                sumaWygranychLacznie += wygrana;
                zmianawygranej = true;

                QString szczegolyWygranej;
                for (auto it = wynikWygranej.begin(); it != wynikWygranej.end(); ++it) {
                    szczegolyWygranej += QString("%1x %2 : %3\n")
                    .arg(it.value().first)
                        .arg(it.key())
                        .arg(it.value().second);
                }

                float sumaWygranych = 0;
                for (auto it = wynikWygranej.begin(); it != wynikWygranej.end(); ++it) {
                    sumaWygranych += it.value().second;
                }

                ui->infoLabel->setText(QString("Wygrana: %1\n%2").arg(sumaWygranych).arg(szczegolyWygranej));
                QCoreApplication::processEvents(); // <- pozwól GUI się zaktualizować
                QThread::sleep(1); // <- i dopiero teraz śpimy
            }
            else
            {
                if (zmianawygranej == false) ui->infoLabel->setText("Brak wygranej");
            }
        } while (czywygrane);

        if (sumabonusów>=l_bonus) freespiny += l_dodatkowychFreeSpinow;
        ui->liczbaFreeSpinow->setText(QString("FreeSpiny: %1").arg(freespiny));
    }

    saldo += sumaWygranychLacznie;
    Wygrane zapisywacz;
    zapisywacz.zapisz1(sumaWygranychLacznie, "🎁", 0);

    AktualizujSaldo();
    bonus = false;
}

void OknoGra1::LosujOdNowa()
{
    if (saldo < stawka) {
        QMessageBox::warning(this, "Bieda", "Za małe saldo aby spinować");
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
                int x = PrzypiszOwocek();
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
    p_japko = ui->JapkoEdit->text().isEmpty() ? 30 : ui->JapkoEdit->text().toInt();
    p_banan = ui->BananEdit->text().isEmpty() ? 20 : ui->BananEdit->text().toInt();
    p_winogrono = ui->WinogronkoEdit->text().isEmpty() ? 15 : ui->WinogronkoEdit->text().toInt();
    p_wisnia = ui->WisniaEdit->text().isEmpty() ? 13 : ui->WisniaEdit->text().toInt();
    p_ananas = ui->AnanasEdit->text().isEmpty() ? 10 : ui->AnanasEdit->text().toInt();
    p_kiwi = ui->KiwiEdit->text().isEmpty() ? 8 : ui->KiwiEdit->text().toInt();
    p_bonus = ui->BonusEdit->text().isEmpty() ? 4 : ui->BonusEdit->text().toInt();

    // Ustawiamy na 0 wszystko co ujemne
    if (p_japko < 0)
        p_japko = 0;
    if (p_banan < 0)
        p_banan = 0;
    if (p_winogrono < 0)
        p_winogrono = 0;
    if (p_wisnia < 0)
        p_wisnia = 0;
    if (p_ananas < 0)
        p_ananas = 0;
    if (p_kiwi < 0)
        p_kiwi = 0;
    if (p_bonus < 0)
        p_bonus = 0;

    // Jeśli wszystkie są zerowe, to ustawiamy bezpiecznie na 1
    if (p_japko == 0 && p_banan == 0 && p_winogrono == 0 && p_wisnia == 0 && p_ananas == 0
        && p_kiwi == 0 && p_bonus == 0) {
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

    l_japko = ui->liczbaSymboliLineEdit_Japko->text().isEmpty()
                  ? 8
                  : ui->liczbaSymboliLineEdit_Japko->text().toInt();
    l_banan = ui->liczbaSymboliLineEdit_Banan->text().isEmpty()
                  ? 8
                  : ui->liczbaSymboliLineEdit_Banan->text().toInt();
    l_winogrono = ui->liczbaSymboliLineEdit_Winogronko->text().isEmpty()
                      ? 8
                      : ui->liczbaSymboliLineEdit_Winogronko->text().toInt();
    l_wisnia = ui->liczbaSymboliLineEdit_Wisnia->text().isEmpty()
                   ? 8
                   : ui->liczbaSymboliLineEdit_Wisnia->text().toInt();
    l_ananas = ui->liczbaSymboliLineEdit_Ananas->text().isEmpty()
                   ? 8
                   : ui->liczbaSymboliLineEdit_Ananas->text().toInt();
    l_kiwi = ui->liczbaSymboliLineEdit_Kiwi->text().isEmpty()
                 ? 8
                 : ui->liczbaSymboliLineEdit_Kiwi->text().toInt();
    l_bonus = ui->liczbaSymboliLineEdit_Bonus->text().isEmpty()
                  ? 4
                  : ui->liczbaSymboliLineEdit_Bonus->text().toInt();

    if (l_japko == 0) {
        l_japko = 8;
        QMessageBox::warning(this, "Niepoprawna wartość", "Niepoprawna minimalna liczba jabłek – ustawiono domyślnie 8.");
    }
    if (l_banan == 0) {
        l_banan = 8;
        QMessageBox::warning(this, "Niepoprawna wartość", "Niepoprawna minimalna liczba bananów – ustawiono domyślnie 8.");
    }
    if (l_winogrono == 0) {
        l_winogrono = 8;
        QMessageBox::warning(this, "Niepoprawna wartość", "Niepoprawna minimalna liczba winogron – ustawiono domyślnie 8.");
    }
    if (l_wisnia == 0) {
        l_wisnia = 8;
        QMessageBox::warning(this, "Niepoprawna wartość", "Niepoprawna minimalna liczba wiśni – ustawiono domyślnie 8.");
    }
    if (l_ananas == 0) {
        l_ananas = 8;
        QMessageBox::warning(this, "Niepoprawna wartość", "Niepoprawna minimalna liczba ananasów – ustawiono domyślnie 8.");
    }
    if (l_kiwi == 0) {
        l_kiwi = 8;
        QMessageBox::warning(this, "Niepoprawna wartość", "Niepoprawna minimalna liczba kiwi – ustawiono domyślnie 8.");
    }
    if (l_bonus == 0) {
        l_bonus = 4;
        QMessageBox::warning(this, "Niepoprawna wartość", "Niepoprawna minimalna liczba bonusów – ustawiono domyślnie 4.");
    }




    QString s;
    bool ok;

    s = ui->kwotaWygranejLineEdit_Japko->text().replace(",", ".");
    w_japko = s.toFloat(&ok);
    if (!ok) {
        w_japko = 0.75;
        QMessageBox::warning(this, "Niepoprawna wartość", "Niepoprawna kwota wygranej dla jabłka – ustawiono domyślnie 0.75.");
    }

    s = ui->kwotaWygranejLineEdit_Banan->text().replace(",", ".");
    w_banan = s.toFloat(&ok);
    if (!ok) {
        w_banan = 1.25;
        QMessageBox::warning(this, "Niepoprawna wartość", "Niepoprawna kwota wygranej dla banana – ustawiono domyślnie 1.25.");
    }

    s = ui->kwotaWygranejLineEdit_Winogronko->text().replace(",", ".");
    w_winogrono = s.toFloat(&ok);
    if (!ok) {
        w_winogrono = 2.0;
        QMessageBox::warning(this, "Niepoprawna wartość", "Niepoprawna kwota wygranej dla winogrona – ustawiono domyślnie 2.0.");
    }

    s = ui->kwotaWygranejLineEdit_Wisnia->text().replace(",", ".");
    w_wisnia = s.toFloat(&ok);
    if (!ok) {
        w_wisnia = 3.0;
        QMessageBox::warning(this, "Niepoprawna wartość", "Niepoprawna kwota wygranej dla wiśni – ustawiono domyślnie 3.0.");
    }

    s = ui->kwotaWygranejLineEdit_Ananas->text().replace(",", ".");
    w_ananas = s.toFloat(&ok);
    if (!ok) {
        w_ananas = 5.0;
        QMessageBox::warning(this, "Niepoprawna wartość", "Niepoprawna kwota wygranej dla ananasa – ustawiono domyślnie 5.0.");
    }

    s = ui->kwotaWygranejLineEdit_Kiwi->text().replace(",", ".");
    w_kiwi = s.toFloat(&ok);
    if (!ok) {
        w_kiwi = 8.0;
        QMessageBox::warning(this, "Niepoprawna wartość", "Niepoprawna kwota wygranej dla kiwi – ustawiono domyślnie 8.0.");
    }



    l_freespin = ui->liczbaFreeSpinowLineEdit->text().isEmpty() ? 10 : ui->liczbaFreeSpinowLineEdit->text().toInt();
    l_dodatkowychFreeSpinow = ui->liczbaDodatkowychSpinowLineEdit->text().isEmpty() ? 1 : ui->liczbaDodatkowychSpinowLineEdit->text().toInt();

    ui->liczbaSymboliLineEdit_Japko->setText(QString::number(l_japko));
    ui->liczbaSymboliLineEdit_Banan->setText(QString::number(l_banan));
    ui->liczbaSymboliLineEdit_Winogronko->setText(QString::number(l_winogrono));
    ui->liczbaSymboliLineEdit_Wisnia->setText(QString::number(l_wisnia));
    ui->liczbaSymboliLineEdit_Ananas->setText(QString::number(l_ananas));
    ui->liczbaSymboliLineEdit_Kiwi->setText(QString::number(l_kiwi));
    ui->liczbaSymboliLineEdit_Bonus->setText(QString::number(l_bonus));


    ui->kwotaWygranejLineEdit_Japko->setText(QString::number(w_japko));
    ui->kwotaWygranejLineEdit_Banan->setText(QString::number(w_banan));
    ui->kwotaWygranejLineEdit_Winogronko->setText(QString::number(w_winogrono));
    ui->kwotaWygranejLineEdit_Wisnia->setText(QString::number(w_wisnia));
    ui->kwotaWygranejLineEdit_Ananas->setText(QString::number(w_ananas));
    ui->kwotaWygranejLineEdit_Kiwi->setText(QString::number(w_kiwi));

    ui->liczbaFreeSpinowLineEdit->setText(QString::number(l_freespin));
    ui->liczbaDodatkowychSpinowLineEdit->setText(QString::number(l_dodatkowychFreeSpinow));

    ZapisDoPliku();
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

void OknoGra1::on_returnButton_select()
{
    WczytajPrawdopodobienstwa();

    this->close();

    if (oknoStartowe) {
        oknoStartowe->show();
        oknoStartowe->AktualizujSaldo();
        oknoStartowe->WczytajDaneGra1();
    } else {
        qWarning() << "oknoStartowe is nullptr!";
    }
}

void OknoGra1::ZapisDoPliku()
{
    QString nazwa_pliku = "danegra1.txt";

    QFile plik(nazwa_pliku);
    if (plik.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&plik);

        /// Zapis prawdopodobieństw
        out << p_japko << "\n" << p_banan << "\n" << p_winogrono << "\n" << p_wisnia << "\n" << p_ananas << "\n" << p_kiwi << "\n" << p_bonus << "\n";

        /// Zapis liczb wymaganych znakow
        out << l_japko << "\n" << l_banan << "\n" << l_winogrono << "\n" << l_wisnia << "\n" << l_ananas << "\n" << l_kiwi << "\n" << l_bonus << "\n";

        /// Zapis mnoznikow
        out << w_japko << "\n" << w_banan << "\n" << w_winogrono << "\n" << w_wisnia << "\n" << w_ananas << "\n" << w_kiwi << "\n";

        /// Zapis bonusu
        out << l_freespin << "\n";
        out << l_dodatkowychFreeSpinow << "\n";



        plik.close();
        qDebug() << "Zapisano do pliku!" << nazwa_pliku;
    } else {
        qDebug() << "Nie udało się otworzyć pliku do zapisu:" << plik.errorString();
    }
}

bool OknoGra1::WczytanieZPliku()
{
    QString nazwa_pliku = "danegra1.txt";
    QFile plik(nazwa_pliku);

    if (plik.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&plik);

        /// Prawdopodobieństwa
        in >> p_japko >> p_banan >> p_winogrono >> p_wisnia >> p_ananas >> p_kiwi >> p_bonus;

        /// Liczby
        in >> l_japko >> l_banan >> l_winogrono >> l_wisnia >> l_ananas >> l_kiwi >> l_bonus;

        /// Mnozniki
        in >> w_japko >> w_banan >> w_winogrono >> w_wisnia >> w_ananas >> w_kiwi;

        /// Bonus
        in >> l_freespin;
        in >> l_dodatkowychFreeSpinow;



        plik.close();
        qDebug() << "Wczytano dane z pliku!";
    }
    else
    {
        qDebug() << "Nie udało się otworzyć pliku do wczytania:" << plik.errorString();
        return false;
    }
    return true;
}
