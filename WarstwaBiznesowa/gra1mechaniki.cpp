#include "gra1mechaniki.h"
#include <QVector>
#include <QMap>
#include <QtWidgets/qlabel.h>

Gra1Mechaniki::Gra1Mechaniki() {

}

Gra1Mechaniki::~Gra1Mechaniki() {

}

QVector<QVector<int>> Gra1Mechaniki::GenerujSymbole(int rows, int cols) {
    QVector<QVector<int>> tablica(rows, QVector<int>(cols)); // Tworzymy dwuwymiarowy wektor o wymiarach rows na cols

    for (int i = 0; i < rows; ++i) // Wypełniamy każdy element losową wartością od 0 do 6 (indeksy symboli)
        for (int j = 0; j < cols; ++j)
            tablica[i][j] = rand() % 7;

    return tablica;
}

int Gra1Mechaniki::PrzypiszOwocek()
{
    if (sumaProporcji == 0) {
        return 6; // Zwracamy bonus, jeśli nie ustawiono prawdopodobieństw
    }

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

void Gra1Mechaniki::UstawPrawdopodobienstwa(int japko, int banan, int winogrono, int wisnia,
                                            int ananas, int kiwi, int bonus,
                                            int l_freespin, int l_dodatkowychFreeSpinow,
                                            int l_japko, int l_banan, int l_winogrono, int l_wisnia,
                                            int l_ananas, int l_kiwi, int l_bonus,
                                            float w_japko, float w_banan, float w_winogrono, float w_wisnia,
                                            float w_ananas, float w_kiwi) {
    // Ustawiamy pola prawdopodobieństwa na nieujemne wartości
    p_japko = std::max(japko, 0);
    p_banan = std::max(banan, 0);
    p_winogrono = std::max(winogrono, 0);
    p_wisnia = std::max(wisnia, 0);
    p_ananas = std::max(ananas, 0);
    p_kiwi = std::max(kiwi, 0);
    p_bonus = std::max(bonus, 0);

    // Jeśli wszystkie wartości są zerowe, ustawiamy domyślnie na 1 (zapobiega błędom losowania)
    if (p_japko + p_banan + p_winogrono + p_wisnia + p_ananas + p_kiwi + p_bonus == 0) {
        p_japko = p_banan = p_winogrono = p_wisnia = p_ananas = p_kiwi = p_bonus = 1;
    }

    // Obliczamy sumę proporcji dla mechanizmu losowania owoców
    sumaProporcji = p_japko + p_banan + p_winogrono + p_wisnia + p_ananas + p_kiwi + p_bonus;

    // Przechowujemy wartości minimalnej liczby symboli wymaganych do wygranej
    this->l_japko = std::max(l_japko, 0);
    this->l_banan = std::max(l_banan, 0);
    this->l_winogrono = std::max(l_winogrono, 0);
    this->l_wisnia = std::max(l_wisnia, 0);
    this->l_ananas = std::max(l_ananas, 0);
    this->l_kiwi = std::max(l_kiwi, 0);
    this->l_bonus = std::max(l_bonus, 0);

    // Przechowujemy wartości wygranych dla każdego owocu
    this->w_japko = w_japko;
    this->w_banan = w_banan;
    this->w_winogrono = w_winogrono;
    this->w_wisnia = w_wisnia;
    this->w_ananas = w_ananas;
    this->w_kiwi = w_kiwi;

    // Przechowujemy liczbę darmowych spinów
    this->l_freespiny = std::max(l_freespiny, 0);
    this->l_dodatkowychFreeSpinow = std::max(l_dodatkowychFreeSpinow, 0);
}

int Gra1Mechaniki::PobierzSumaProporcji() const {
    return sumaProporcji; // Zwracamy sumaProporcji do UI
}

QMap<QString, QPair<int, float>> Gra1Mechaniki::SprawdzWygranaMechanika(const QVector<QVector<QString>>& siatkaTekstow, float stawka) {
    QMap<QString, QPair<int, float>> wynikWygranej; // Przechowuje liczbę trafień i wygraną dla każdego symbolu
    float wygrana = 0;

    int rows = siatkaTekstow.size();
    int cols = rows > 0 ? siatkaTekstow[0].size() : 0;
    int SumaWystapien[7] = {0}; // Inicjalizacja licznika dla każdego symbolu

    // Przechodzimy przez siatkę symboli i zliczamy ich wystąpienia
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            QString tekst = siatkaTekstow[i][j]; // Pobieramy wartość symbolu
            if (tekst == "🍎") SumaWystapien[0]++;
            if (tekst == "🍌") SumaWystapien[1]++;
            if (tekst == "🍇") SumaWystapien[2]++;
            if (tekst == "🍒") SumaWystapien[3]++;
            if (tekst == "🍍") SumaWystapien[4]++;
            if (tekst == "🥝") SumaWystapien[5]++;
            if (tekst == "🎁") SumaWystapien[6]++;
        }
    }

    // Sprawdzamy, czy osiągnięto minimalną liczbę symboli, aby wygrać
    auto dodajWygrana = [&](QString symbol, int liczba, float wartosc) {
        float nagroda = wartosc * stawka; // Obliczamy wartość wygranej na podstawie stawki
        wynikWygranej[symbol] = qMakePair(liczba, nagroda);
    };

    // Jeśli liczba trafień przekracza próg, dodajemy wygraną
    if (SumaWystapien[0] >= l_japko) dodajWygrana("🍎", SumaWystapien[0], w_japko);
    if (SumaWystapien[1] >= l_banan) dodajWygrana("🍌", SumaWystapien[1], w_banan);
    if (SumaWystapien[2] >= l_winogrono) dodajWygrana("🍇", SumaWystapien[2], w_winogrono);
    if (SumaWystapien[3] >= l_wisnia) dodajWygrana("🍒", SumaWystapien[3], w_wisnia);
    if (SumaWystapien[4] >= l_ananas) dodajWygrana("🍍", SumaWystapien[4], w_ananas);
    if (SumaWystapien[5] >= l_kiwi) dodajWygrana("🥝", SumaWystapien[5], w_kiwi);

    return wynikWygranej; // Zwracamy obliczoną wygraną
}

QMap<QString, QPair<int, float>> Gra1Mechaniki::BonusMechanika(const QVector<QVector<QString>>& siatkaTekstow, int l_freespiny, int l_dodatkowychFreeSpinow, float stawka) {
    QMap<QString, QPair<int, float>> wynikWygranej; // Przechowuje wygrane symbole i ich wartość
    bool czywygrane; // Flaga sprawdzająca, czy coś zostało wygrane
    float sumaWygranychLacznie = 0; // Całkowita wartość wygranej

    while (l_freespiny > 0) { // Główna pętla darmowych spinów
        l_freespiny--;
        int sumabonusów = 0; // Licznik trafień symboli (bonus)

        do { // Pętla sprawdzająca wygrane w danym spinie
            sumabonusów = 0;
            czywygrane = false;
            float wygrana = 0; // Obliczona wygrana w danym spinie
            int rows = siatkaTekstow.size();
            int cols = rows > 0 ? siatkaTekstow[0].size() : 0;

            int SumaWystapien[7] = {0}; // Liczenie symboli

            // Zliczanie wystąpień symboli w siatce
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    QString tekst = siatkaTekstow[i][j]; // Pobranie symbolu z siatki
                    if (tekst == "🍎") SumaWystapien[0]++;
                    if (tekst == "🍌") SumaWystapien[1]++;
                    if (tekst == "🍇") SumaWystapien[2]++;
                    if (tekst == "🍒") SumaWystapien[3]++;
                    if (tekst == "🍍") SumaWystapien[4]++;
                    if (tekst == "🥝") SumaWystapien[5]++;
                    if (tekst == "🎁") sumabonusów++; // Liczenie trafień
                }
            }

            // Sprawdzanie, czy osiągnięto minimalną liczbę symboli do wygranej
            auto dodajWygrana = [&](QString symbol, int liczba, float wartosc) {
                float nagroda = wartosc * stawka; // Obliczamy wygraną na podstawie stawki
                wynikWygranej[symbol] = wynikWygranej.contains(symbol)
                                            ? qMakePair(wynikWygranej[symbol].first + 1, wynikWygranej[symbol].second + nagroda)
                                            : qMakePair(1, nagroda);
                czywygrane = true; // Oznaczamy, że był trafiony symbol
            };

            // Dodajemy wygrane, jeśli przekroczyły wymagany próg
            if (SumaWystapien[0] >= l_japko) dodajWygrana("🍎", SumaWystapien[0], w_japko);
            if (SumaWystapien[1] >= l_banan) dodajWygrana("🍌", SumaWystapien[1], w_banan);
            if (SumaWystapien[2] >= l_winogrono) dodajWygrana("🍇", SumaWystapien[2], w_winogrono);
            if (SumaWystapien[3] >= l_wisnia) dodajWygrana("🍒", SumaWystapien[3], w_wisnia);
            if (SumaWystapien[4] >= l_ananas) dodajWygrana("🍍", SumaWystapien[4], w_ananas);
            if (SumaWystapien[5] >= l_kiwi) dodajWygrana("🥝", SumaWystapien[5], w_kiwi);

            if (czywygrane) sumaWygranychLacznie += wygrana; // Dodanie wygranej do całkowitej sumy

        } while (czywygrane); // Powtarzamy dopóki trafiamy wygrane symbole

        if (sumabonusów >= l_bonus) l_freespiny += l_dodatkowychFreeSpinow; // Jeśli trafiliśmy , dodajemy dodatkowe spiny
    }

    wynikWygranej["TOTAL"] = qMakePair(0, sumaWygranychLacznie); // Przekazanie całkowitej wygranej do UI
    return wynikWygranej;
}

int Gra1Mechaniki::PobierzLiczbeFreeSpinow() const {
    return l_freespiny;
}

int Gra1Mechaniki::PobierzLiczbeDodatkowychFreeSpinow() const {
    return l_dodatkowychFreeSpinow;
}
