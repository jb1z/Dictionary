//основное окно
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include <QPalette>
#include "dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Dialog dialog;
    QPalette* pallete;
    Ui::Widget *ui;
};
#endif
