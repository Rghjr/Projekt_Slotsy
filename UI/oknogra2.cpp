#include "oknogra2.h"
#include "ui_oknogra2.h"

OknoGra2::OknoGra2(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::OknoGra2)
{
    ui->setupUi(this);
}

OknoGra2::~OknoGra2()
{
    delete ui;
}
