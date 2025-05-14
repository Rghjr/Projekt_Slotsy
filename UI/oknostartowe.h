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
    OknoStartowe(QWidget *parent = nullptr);
    ~OknoStartowe();

private slots:


    void on_exitButton_clicked();

    void on_secondGameButton_clicked();

    void on_firstGameButton_clicked();

private:
    Ui::OknoStartowe *ui;
};
#endif // OKNOSTARTOWE_H
