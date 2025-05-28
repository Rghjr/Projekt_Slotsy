#ifndef OBSLUGAWYJATKOW_H
#define OBSLUGAWYJATKOW_H

#include <exception>

class ZlyInput : public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "Niepoprawne dane wejściowe";
    }
};

class PonizejZera : public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "Saldo poniżej zera";
    }
};

#endif // OBSLUGAWYJATKOW_H
