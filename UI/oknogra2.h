#ifndef OKNOGRA2_H
#define OKNOGRA2_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class OknoGra2;
}
QT_END_NAMESPACE

class OknoGra2 : public QMainWindow
{
    Q_OBJECT

public:
    OknoGra2(QWidget *parent = nullptr);
    ~OknoGra2();

private slots:


private:
    Ui::OknoGra2 *ui;
};

#endif // OKNOGRA2_H
