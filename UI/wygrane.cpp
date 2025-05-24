#include "wygrane.h"
#include <QFile>
#include <QTextStream>

Wygrane::Wygrane() : data("") {}

Wygrane::Wygrane(const QString &text) : data(text) {}

Wygrane::Wygrane(const char* text) : data(QString::fromUtf8(text)) {}

QString Wygrane::getText() const {
    return data;
}

void Wygrane::setText(const QString &text) {
    data = text;
}

int Wygrane::length() const {
    return data.length();
}

void Wygrane::append(const QString &other) {
    data.append(other);
}

QString formatWygrana(float kwota, const QString& symbol, int ilosc) {
    return QString("%1 - %2 - %3")
    .arg(kwota, 0, 'f', 2)
        .arg(symbol)
        .arg(ilosc);
}

void Wygrane::zapisz1(float kwota, const QString &symbol, int ilosc) {
    QString linia = QString("%1 - %2 - %3")
    .arg(kwota, 0, 'f', 2)
        .arg(symbol)
        .arg(ilosc);

    QFile file("wygrane_1.txt");
    QString staraZawartosc;

    // 1. Wczytaj starą zawartość pliku (jeśli istnieje)
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        staraZawartosc = in.readAll();
        file.close();
    }

    // 2. Otwórz plik do zapisu (nadpisanie)
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        // najpierw nowa linia, potem stara zawartość
        out << linia << "\n" << staraZawartosc;
        file.close();
    }
}

void Wygrane::zapisz2(float kwota, const QString &symbol, int ilosc) {
    QString linia = QString("%1 - %2 - %3")
    .arg(kwota, 0, 'f', 2)
        .arg(symbol)
        .arg(ilosc);

    QFile file("wygrane_2.txt");
    QString staraZawartosc;

    // 1. Wczytaj starą zawartość pliku (jeśli istnieje)
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        staraZawartosc = in.readAll();
        file.close();
    }

    // 2. Otwórz plik do zapisu (nadpisanie)
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        // najpierw nowa linia, potem stara zawartość
        out << linia << "\n" << staraZawartosc;
        file.close();
    }
}

