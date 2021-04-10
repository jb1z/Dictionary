#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    pallete = new QPalette();
    // установка цвета заднего фона инфомармационного окна и цвета кнопки в этом окне
    pallete -> setColor(QPalette::Background, QColor(240,99,57));
    setAutoFillBackground(true);
    setPalette(*(pallete));
    ui->pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(250, 110, 123);"));
}

void Dialog::on_pushButton_clicked()
{
    this->close();
}

Dialog::~Dialog()
{
    delete ui;
}

