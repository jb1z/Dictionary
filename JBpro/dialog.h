// информационное окно
#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPalette>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushButton_clicked();

private:
    QPalette* pallete;
    Ui::Dialog *ui;
};

#endif // DIALOG_H
