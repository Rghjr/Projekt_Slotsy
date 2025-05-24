#ifndef OKNOSTARTOWE_H
#define OKNOSTARTOWE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class OknoStartowe;
}
QT_END_NAMESPACE

class OknoStartowe : public QMainWindow
{
    Q_OBJECT


public:
    float saldo = 100;

    void ustawSaldo(float nowe) { saldo = nowe; }
    float pobierzSaldo() const { return saldo; }

    OknoStartowe(QWidget *parent = nullptr);
    ~OknoStartowe();
    void EdytujSaldoPlus();
    void EdytujSaldoMinus();



private slots:


    void on_exitButton_clicked();

    void on_secondGameButton_clicked();

    void on_firstGameButton_clicked();

private:
    Ui::OknoStartowe *ui;
};
#endif // OKNOSTARTOWE_H
