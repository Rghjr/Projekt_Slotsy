#ifndef MYSTRING_H
#define MYSTRING_H

#include <QString>

class Wygrane
{
public:
    Wygrane();                              // konstruktor domyślny
    Wygrane(const QString &text);           // konstruktor z QString
    Wygrane(const char* text);              // konstruktor z C-string

    QString getText() const;
    void setText(const QString &text);
    int length() const;
    void append(const QString &other);
    QString toUpper() const;
    QString toLower() const;
    void zapisz1(float kwota, const QString &symbol, int ilosc);
    void zapisz2(float kwota, const QString &symbol, int ilosc);

private:
    QString data;

};

#endif // MYSTRING_H
