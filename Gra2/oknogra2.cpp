#include "oknogra2.h"
#include "ui_oknogra2.h"
#include "obslugawyjatkow.h"
#include <QFont>
#include <QThread>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QTimer>
#include <QFile>
#include <QLineEdit>
#include <QTextStream>
#include <QMessageBox>
#include "wygrane.h"


OknoGra2::OknoGra2(OknoStartowe* startoweOkno, QWidget *parent)
    : OknoGra1(startoweOkno, parent)
    , ui(new Ui::OknoGra2)
    , oknoStartowe(startoweOkno)
{
    ui->setupUi(this);

    /// USTAWIENIE WSZYSTKIEGO CO MUSI BYĆ

    connect(ui->powrotButton, &QPushButton::clicked, this, &OknoGra2::on_returnButton_select);


    connect(ui->SPINPRZYCISK, &QPushButton::clicked, this, &OknoGra2::LosujOdNowa);

    ui->AUTOSPINPRZYCISK->setCheckable(true);
    connect(ui->AUTOSPINPRZYCISK, &QPushButton::toggled, this, &OknoGra2::Autospin);

    ui->stawkaComboBox->setCurrentIndex(6); // bo indeksy startują od 0
    connect(ui->stawkaComboBox, &QComboBox::currentTextChanged, this, &OknoGra2::zmienStawke);

    saldo = oknoStartowe->pobierzSaldo();
    ui->saldoLabel->setText(QString("Saldo: %1").arg(QString::number(saldo, 'f', 2)));

    bonus = false;
    spiny_bonus = 0;

    //Domyślne wartości po otwarciu okna
    ui->JapkoEdit->setText("30");
    ui->BananEdit->setText("25");
    ui->WinogronkoEdit->setText("20");
    ui->WisniaEdit->setText("15");
    ui->BonusEdit->setText("10");

    ui->kwotaWygranejLineEdit_Japko->setText("0.75");
    ui->kwotaWygranejLineEdit_Banan_->setText("1.25");
    ui->kwotaWygranejLineEdit_Winogronko_->setText("2.0");
    ui->kwotaWygranejLineEdit_Wisnia->setText("3.0");
    ui->kwotaWygranejLineEdit_Bonus->setText("5.0");

    ui->mnoznikBonusuLineEdit->setText("10.0");
    ui->Freespiny_Label->setText(QString("FreeSpiny: %1").arg(spiny_bonus));
    ui->LiczbaFreeSpinowLineEdit->setText("5");
    ui->LiczbaDodatkowychFreeSpinowLineEdit->setText("1");

    /// WCZYTANIE Z PLIKU I USTAWIENIE WSZYSTKIEGO WEDŁUG TEGO
    if (WczytanieZPliku())
    {
        if (l1) ui->l_1_check->setChecked(true);
        if (l2) ui->l_2_check->setChecked(true);
        if (l3) ui->l_3_check->setChecked(true);
        if (l4) ui->l_4_check->setChecked(true);
        if (l5) ui->l_5_check->setChecked(true);
        if (l6) ui->l_6_check->setChecked(true);
        if (l7) ui->l_7_check->setChecked(true);
        if (l8) ui->l_8_check->setChecked(true);
        if (l9) ui->l_9_check->setChecked(true);
        if (l10) ui->l_10_check->setChecked(true);
        if (l11) ui->l_11_check->setChecked(true);
        if (l12) ui->l_12_check->setChecked(true);
        if (l13) ui->l_13_check->setChecked(true);
        if (l14) ui->l_14_check->setChecked(true);
        if (l15) ui->l_15_check->setChecked(true);
        if (l16) ui->l_16_check->setChecked(true);
        if (l17) ui->l_17_check->setChecked(true);

        /// PRAWDOPODOBIEŃSTWA
        ui->JapkoEdit->setText(QString::number(p_japko));
        ui->BananEdit->setText(QString::number(p_banan));
        ui->WinogronkoEdit->setText(QString::number(p_winogrono));
        ui->WisniaEdit->setText(QString::number(p_wisnia));
        ui->BonusEdit->setText(QString::number(p_bonus));

        /// WYGRANE
        ui->kwotaWygranejLineEdit_Japko->setText(QString::number(w_japko));
        ui->kwotaWygranejLineEdit_Banan_->setText(QString::number(w_banan));
        ui->kwotaWygranejLineEdit_Winogronko_->setText(QString::number(w_winogrono));
        ui->kwotaWygranejLineEdit_Wisnia->setText(QString::number(w_wisnia));
        ui->kwotaWygranejLineEdit_Bonus->setText(QString::number(w_bonus));

        /// BONUS
        ui->mnoznikBonusuLineEdit->setText(QString::number(mn_bonus));
        ui->Freespiny_Label->setText(QString("FreeSpiny: %1").arg(spiny_bonus));
        ui->LiczbaFreeSpinowLineEdit->setText(QString::number(l_freespin));
        ui->LiczbaDodatkowychFreeSpinowLineEdit->setText(QString::number(l_dodatkowychFreeSpinow));
    }
    else
    {
        ui->l_1_check->setChecked(true);
        ui->l_2_check->setChecked(true);
        ui->l_3_check->setChecked(true);
        ui->l_4_check->setChecked(true);
        ui->l_5_check->setChecked(true);

        WczytajPrawdopodobienstwa();
    }
}

OknoGra2::~OknoGra2()
{
    delete ui;
}

void OknoGra2::UstawGrid(const QVector<QVector<int>>& tablica, int rows, int cols)
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
    try{
    if (saldo < stawka)
    {
        QMessageBox::warning(this, "Bieda", "Za małe saldo aby spinować");
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
    if (bonus && spiny_bonus > 0) SprawdzWygranaBonus();
    else SprawdzWygrana();

    ui->Freespiny_Label->setText(QString("FreeSpiny: %1").arg(spiny_bonus));
    }
    catch (std::exception& ZlyInput)
    {
        QMessageBox::warning(this, "Błąd wejścia", ZlyInput.what());
        ui->SPINPRZYCISK->setEnabled(true);
        return;
    }
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
    bool ok;
    //obsługa wyjątków - sprawdzenie czy wartości są poprawnie wprowadzone
    std::vector<int*> elem_int = {&p_japko, &p_banan, &p_winogrono, &p_wisnia, &p_bonus, &l_freespin, &l_dodatkowychFreeSpinow};
    std::vector<QLineEdit*> edits_int = {ui->JapkoEdit,
                                      ui->BananEdit,
                                      ui->WinogronkoEdit,
                                      ui->WisniaEdit,
                                      ui->BonusEdit,
                                      ui->LiczbaFreeSpinowLineEdit,
                                      ui->LiczbaDodatkowychFreeSpinowLineEdit};

    auto it_elem_int = elem_int.begin();
    auto it_edits_int = edits_int.begin();


    while (it_elem_int != elem_int.end() && it_edits_int != edits_int.end()) //iteruje przez wartości i sprawdza ich konwersje do int
    {
        **it_elem_int = (*it_edits_int)->text().toInt(&ok);
        if (!ok || **it_elem_int < 0) { ok = false; break; }
        ++it_elem_int;  // Przesunięcie iteratora
        ++it_edits_int;
    }

    if (!ok) throw ZlyInput();

    // Jeśli wszystkie są zerowe, to ustawiamy bezpiecznie na 1
    if (p_japko == 0 && p_banan == 0 && p_winogrono == 0 && p_wisnia == 0 && p_bonus == 0)
    {
        p_japko = p_banan = p_winogrono = p_wisnia = p_bonus = 1;
    }

    // ustawiamy na domyślne jeżeli nie poprawne wygrane
    QString s_w;
    std::vector<float*> elem_float = {&w_japko, &w_banan, &w_winogrono, &w_wisnia, &w_bonus, &mn_bonus};
    std::vector<QLineEdit*> edits_float = {ui->kwotaWygranejLineEdit_Japko,
                                    ui->kwotaWygranejLineEdit_Banan_,
                                    ui->kwotaWygranejLineEdit_Winogronko_,
                                    ui->kwotaWygranejLineEdit_Wisnia,
                                    ui->kwotaWygranejLineEdit_Bonus,
                                    ui->mnoznikBonusuLineEdit};

    auto it_elem_float = elem_float.begin();
    auto it_edits_float = edits_float.begin();

    while (it_elem_float != elem_float.end() && it_edits_float != edits_float.end()) //iteruje przez wartości i sprawdza ich konwersje do float
    {
        s_w = (*it_edits_float)->text().replace(",", ".");
        **it_elem_float = s_w.toFloat(&ok);
        if (!ok || **it_elem_float < 0) { ok = false; break; }
        ++it_elem_float;  // Przesunięcie iteratora
        ++it_edits_float;
    }

    if (!ok) throw ZlyInput();

    // Obliczamy sumę proporcji
    sumaProporcji = p_japko + p_banan + p_winogrono + p_wisnia + p_bonus;

    // Ustawiamy te wartości z powrotem do QLineEdit, żeby było widać co naprawdę siedzi
    ui->JapkoEdit->setText(QString::number(p_japko));
    ui->BananEdit->setText(QString::number(p_banan));
    ui->WinogronkoEdit->setText(QString::number(p_winogrono));
    ui->WisniaEdit->setText(QString::number(p_wisnia));
    ui->BonusEdit->setText(QString::number(p_bonus));

    ui->kwotaWygranejLineEdit_Japko->setText(QString::number(w_japko));
    ui->kwotaWygranejLineEdit_Banan_->setText(QString::number(w_banan));
    ui->kwotaWygranejLineEdit_Winogronko_->setText(QString::number(w_winogrono));
    ui->kwotaWygranejLineEdit_Wisnia->setText(QString::number(w_wisnia));
    ui->kwotaWygranejLineEdit_Bonus->setText(QString::number(w_bonus));

    ui->mnoznikBonusuLineEdit->setText(QString::number(mn_bonus));
    ui->LiczbaFreeSpinowLineEdit->setText(QString::number(l_freespin));
    ui->LiczbaDodatkowychFreeSpinowLineEdit->setText(QString::number(l_dodatkowychFreeSpinow));



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

    ZapisDoPliku();
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

    saldo += wygrana;
    AktualizujSaldo();

    if ( bonusCount != 0 )
    {
        bonus = true;
        spiny_bonus = l_freespin + (bonusCount-1) * l_dodatkowychFreeSpinow;
        ui->WygraneLabel->setText("BONUS");
        QString wynikTekst = QString("Łączna wygrana: %1\n").arg(wygrana);
        ui->LacznaWygrana_Label->setText(wynikTekst);
    }
    else
    {
        QString wynikTekst = QString("Łączna wygrana: %1\n").arg(wygrana);
        ui->LacznaWygrana_Label->setText(wynikTekst);
    }
}

void OknoGra2::SprawdzWygranaBonus()
{
    WczytajPrawdopodobienstwa();

    ui->WygraneLabel->clear();
    ui->WygraneLabel->setText("BONUS");  // Dodano nagłówek

    float wygrana = 0;
    bool anyWin = false;

    QString a00 = gridLabels[0][0]->text();
    QString a01 = gridLabels[0][1]->text();
    QString a02 = gridLabels[0][2]->text();

    QString a10 = gridLabels[1][0]->text();
    QString a11 = gridLabels[1][1]->text();
    QString a12 = gridLabels[1][2]->text();

    QString a20 = gridLabels[2][0]->text();
    QString a21 = gridLabels[2][1]->text();
    QString a22 = gridLabels[2][2]->text();

    auto liniaWygrana = [](QString x, QString y, QString z) -> bool {
        if (x == "🎁") x = (y != "🎁") ? y : z;
        if (y == "🎁") y = (x != "🎁") ? x : z;
        if (z == "🎁") z = (x != "🎁") ? x : y;
        return (x == y && y == z);
    };

    if (l1 && liniaWygrana(a00, a01, a02)) { wygrana += Winek(1); anyWin = true; }
    if (l2 && liniaWygrana(a10, a11, a12)) { wygrana += Winek(2); anyWin = true; }
    if (l3 && liniaWygrana(a20, a21, a22)) { wygrana += Winek(3); anyWin = true; }

    if (l4 && liniaWygrana(a00, a11, a22)) { wygrana += Winek(4); anyWin = true; }
    if (l5 && liniaWygrana(a20, a11, a02)) { wygrana += Winek(5); anyWin = true; }

    if (l6 && liniaWygrana(a20, a11, a22)) { wygrana += Winek(6); anyWin = true; }
    if (l7 && liniaWygrana(a10, a01, a12)) { wygrana += Winek(7); anyWin = true; }

    if (l8 && liniaWygrana(a00, a11, a02)) { wygrana += Winek(8); anyWin = true; }
    if (l9 && liniaWygrana(a10, a21, a12)) { wygrana += Winek(9); anyWin = true; }

    if (l10 && liniaWygrana(a20, a21, a12)) { wygrana += Winek(10); anyWin = true; }
    if (l11 && liniaWygrana(a10, a11, a02)) { wygrana += Winek(11); anyWin = true; }

    if (l12 && liniaWygrana(a00, a01, a12)) { wygrana += Winek(12); anyWin = true; }
    if (l13 && liniaWygrana(a10, a11, a22)) { wygrana += Winek(13); anyWin = true; }

    if (l14 && liniaWygrana(a10, a01, a02)) { wygrana += Winek(14); anyWin = true; }
    if (l15 && liniaWygrana(a20, a11, a12)) { wygrana += Winek(15); anyWin = true; }

    if (l16 && liniaWygrana(a00, a11, a12)) { wygrana += Winek(16); anyWin = true; }
    if (l17 && liniaWygrana(a10, a11, a02)) { wygrana += Winek(17); anyWin = true; }

    QString wynikTekst = QString("Łączna wygrana: %1\n").arg(wygrana);
    ui->LacznaWygrana_Label->setText(wynikTekst);

    spiny_bonus--;
    if (spiny_bonus == 0) bonus = false;
    saldo += wygrana;
    AktualizujSaldo();
}

float OknoGra2::Winek(int x)
{
    WczytajPrawdopodobienstwa();

    int row = 0;
    if (x == 1 || x == 4 || x == 8 || x == 12 || x == 16) row = 0;
    else if (x == 2 || x == 7 || x == 9 || x == 11 || x == 13 || x == 14 || x == 17) row = 1;
    else if (x == 3 || x == 5 || x == 6 || x == 10 || x == 15) row = 2;
    else return 0;

    QString z0 = gridLabels[row][0]->text();
    QString z1 = gridLabels[row][1]->text();
    QString z2 = gridLabels[row][2]->text();

    // Jeśli pierwszy to 🎁, znajdź alternatywny symbol
    QString znak;
    if (z0 == "🎁") {
        if (z1 != "🎁") znak = z1;
        else if (z2 != "🎁") znak = z2;
        else znak = "🎁"; // domyślny symbol, gdy wszystkie to 🎁
    } else {
        znak = z0;
    }

    QMap<QString, float> wspMap {
        {"🍎", w_japko},
        {"🍌", w_banan},
        {"🍇", w_winogrono},
        {"🍒", w_wisnia},
        {"🎁", w_bonus} // Technicznie nie powinien być używany
    };

    float wsp = wspMap.value(znak, 0.0f);
    float wygrana = stawka * wsp;

    if (bonus)
    {
        wygrana *= mn_bonus;
        Wygrane zapisywacz;
        zapisywacz.zapisz2(wygrana, "🎁", x);
    }
    else
    {
        Wygrane zapisywacz;
        zapisywacz.zapisz2(wygrana, znak, x);
    }

    QString currentText = ui->WygraneLabel->text();
    currentText += QString("\nLinia %1: %2 - wygrana: %3").arg(x).arg(znak).arg(wygrana);
    ui->WygraneLabel->setText(currentText);

    return wygrana;
}

void OknoGra2::AktualizujSaldo()
{
    oknoStartowe->ustawSaldo(saldo);
    ui->saldoLabel->setText(QString("Saldo: %1").arg(QString::number(saldo, 'f', 2)));
}

void OknoGra2::zmienStawke(const QString &tekst)
{
    float nowaStawka = ui->stawkaComboBox->currentText().toFloat();
    stawka = nowaStawka;
}

void OknoGra2::on_returnButton_select()
{
    try {
    WczytajPrawdopodobienstwa();

    this->close();

    if (oknoStartowe) {
        oknoStartowe->show();
        oknoStartowe->AktualizujSaldo();
        oknoStartowe->WczytajDaneGra2();
    } else {
        qWarning() << "oknoStartowe is nullptr!";
    }
    }
    catch (std::exception& ZlyInput)
    {
        QMessageBox::warning(this, "Błąd wejścia", ZlyInput.what());
        return;
    }
}

void OknoGra2::ZapisDoPliku()
{
    QString nazwa_pliku = "danegra2.txt";

    QFile plik(nazwa_pliku);
    if (plik.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&plik);

        /// Zapis prawdopodobieństw co linijke
        out << p_japko << "\n" << p_banan << "\n" << p_winogrono << "\n" << p_wisnia << "\n" << p_bonus << "\n";

        /// Zapis wygranych co linijke
        out << w_japko << "\n" << w_banan << "\n" << w_winogrono << "\n" << w_wisnia << "\n" << w_bonus << "\n";

        /// Zapis danych bonusu
        out << mn_bonus << "\n" << l_freespin << "\n" << l_dodatkowychFreeSpinow << "\n" << bonus << "\n" << spiny_bonus << "\n";

        /// Zapis linii
        out << l1 << "\n" << l2 << "\n" << l3 << "\n" << l4 << "\n" << l5 << "\n" << l6 << "\n" << l7 << "\n" << l8 << "\n" << l9 << "\n" << l10 << "\n" << l11 << "\n" << l12 << "\n" << l13 << "\n" << l14 << "\n" << l15 << "\n" << l16 << "\n" << l17 << "\n";

        plik.close();
        qDebug() << "Zapisano do pliku!" << nazwa_pliku;
    } else {
        qDebug() << "Nie udało się otworzyć pliku do zapisu:" << plik.errorString();
    }
}

bool OknoGra2::WczytanieZPliku()
{
    QString nazwa_pliku = "danegra2.txt";
    QFile plik(nazwa_pliku);

    if (plik.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&plik);

        // Prawdopodobieństwa (int)
        in >> p_japko >> p_banan >> p_winogrono >> p_wisnia >> p_bonus;

        // Wygrane (float)
        in >> w_japko >> w_banan >> w_winogrono >> w_wisnia >> w_bonus;

        // Bonus dane (float + int + bool + int)
        in >> mn_bonus >> l_freespin >> l_dodatkowychFreeSpinow;

        int bonusInt;
        in >> bonusInt;
        bonus = (bonusInt != 0);

        in >> spiny_bonus;



        int linie[17];
        for (int i = 0; i < 17; ++i) {
            in >> linie[i];
        }
        l1 = linie[0]; l2 = linie[1]; l3 = linie[2]; l4 = linie[3]; l5 = linie[4];
        l6 = linie[5]; l7 = linie[6]; l8 = linie[7]; l9 = linie[8]; l10 = linie[9];
        l11 = linie[10]; l12 = linie[11]; l13 = linie[12]; l14 = linie[13]; l15 = linie[14];
        l16 = linie[15]; l17 = linie[16];

        plik.close();
        qDebug() << "Wczytano dane z pliku!" << nazwa_pliku;
    }
    else
    {
        qDebug() << "Nie udało się otworzyć pliku do wczytania:" << plik.errorString();
        return false;
    }
    return true;
}
