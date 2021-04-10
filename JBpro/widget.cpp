#include "widget.h"
#include "ui_widget.h"
#include "dialog.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QColor>
#include <QCoreApplication>
bool vkl = 0;// для информационного окна (при первом запуске отобржается дополнительная информация с просьбой о прочтении интрукции перед использованием программы)
Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    pallete = new QPalette();
    pallete -> setColor(QPalette::Background, QColor(240,99,57));// установка цвета палитры для заднего фона
    setAutoFillBackground(true);
    setPalette(*(pallete));
    // установка цвета кнопок и начальных значений "активности" некоторых объектов
    ui->pushButton_3->setStyleSheet(QString::fromUtf8("background-color: rgb(250, 110, 123);"));
    ui->pushButton_2->setStyleSheet(QString::fromUtf8("background-color: rgb(250, 110, 123);"));
    ui->pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(250, 110, 123);"));
    ui->pushButton_2->setEnabled(0);
    ui->pushButton->setEnabled(0);
    ui->lineEdit->setEnabled(0);
    ui->textEdit->setReadOnly(1);
    ui->textEdit_2->setReadOnly(1);
}
void Widget::on_pushButton_clicked()
{
    ui->textEdit->clear();// очищение поля вывода
    ui->textEdit_2->clear();// очищение поля вывода
    ui->label_7->clear();// очищение поля вывода
    ui->textEdit->setTextColor(QColor(0,0,0));// установка цвета текста поля вывода
    ui->textEdit_2->setTextColor(QColor(0,0,0));// установка цвета текста поля вывода
    QString str = "";// переменная, считывающая вводимое слово
    QString strI = "";// переменная, хранящая очередное слово из файла
    QString buffer = "";// переменная для обработки слова "побуквенно" (для установки цвета)
    QString inter1 = "";// переменная для формирования строки вывода количества найденных слов в реальном времени
    QString inter2 = "";// переменная для формирования строки вывода количества найденных слов в реальном времени
    str = ui->lineEdit->text();
    bool proverka = 0;// "флаг" для проверки слова
    // неверным считается тот ввод, в котором присутствуют знаки отличные от букв английского алфавита или пустая строка
    int prq = 0 ;
    if(str == "") proverka = 1;
    for(int i = 0; i < str.length();i++)
    {
        prq = (int)str[i].toLatin1();
        if(prq < 65 || prq > 122 || (prq > 90 && prq < 97 ))
        {
            proverka = 1;
            break;
        }
    }

    if(proverka == 0)
    {
        ui->label_7->setText("Searching...");
        QFile nFile("words.txt");
        int countObr = 0;// индекс буквы подстроки
        int N1 = 0;// переменная подсчёта совпадения букв слова из файла и введененого слова
        int count1 = 0;// подсчёт количетсва совпадений по поиску по подстроке
        int count2 = 0;// подсчёт количетсва совпадений по посимвольному поиску
        int pr;// перменная для хранения ASCII кода буквы слова
        int pr1;// перменная для хранения ASCII кода буквы слова
        int hlp = 0;// коэффициент +-32 для одинаковой обработки верхнего/нижнего регистра
        int promej = 0;// переменная для хранения числа разрывов в слове букв введенного слова (прим. - подстрока(cat), слово(climate) => 4 промежутка)
        bool promejF = 0;// наличие промежутка (есть/нет)
        // открытие и обработка словаря из файла
        if(nFile.open(QFile::ReadOnly))
        {
            QTextStream stream(&nFile);
            do
            {
                strI = stream.readLine();
                if(strI != "")
                {
                    // подсчёт совпадений букв подстроки и слова из словаря
                    for(int i = 0; i < strI.length();i++)
                    {
                        pr = (int)str[countObr].toLatin1();
                        pr1 = (int)strI[i].toLatin1();
                        if(pr >= 97) hlp = -32;
                        else hlp = 32;
                        if(pr == pr1 || pr  + hlp == pr1)
                        {
                            promejF = 1;
                            if(countObr < str.length() - 1)
                            {
                                countObr++;
                            }
                            N1++;
                        }
                        else
                        {
                            if(promejF == 1 && N1 != str.length()) promej++;
                        }
                    }
                    if(N1 == str.length())
                    {
                        // если слово подошло печатаем его в textEdit (с выделением красным цветом букв подстроки)
                        countObr=0;
                        N1=0;
                        // если слово содержит подстроку целиком (cat - bobCAT) - печатаем в поле для поиска по подстроке, иначе в поле для поиска посмивольно
                        if(promej == 0)
                        {
                            for(int i = 0; i < strI.length();i++)
                            {
                                pr = (int)str[countObr].toLatin1();
                                pr1 = (int)strI[i].toLatin1();
                                if(pr >= 97) hlp = -32;
                                else hlp = 32;
                                if(pr == pr1 || pr  + hlp == pr1)
                                {
                                    buffer = strI[i];
                                    ui->textEdit_2->setTextColor(QColor(255,0,0));
                                    ui->textEdit_2->insertPlainText(buffer);
                                    ui->textEdit_2->setTextColor(QColor(0,0,0));
                                    if(countObr < str.length() - 1)
                                    {
                                        countObr++;
                                    }
                                    N1++;
                                }
                                else
                                {
                                    buffer = strI[i];
                                    ui->textEdit_2->insertPlainText(buffer);
                                }
                            }
                            buffer = "";
                            ui->textEdit_2->append("");
                            QCoreApplication::processEvents();
                            count1++;
                            inter1.setNum(count1);
                            if(count1 == 1) inter1+=" match was found.";
                            else inter1+=" matches were found";
                            if(count1 > 0) ui->label_3->setText(inter1);
                            else ui->label_3->setText("Nothing were found still.");
                        }
                        else
                        {
                            for(int i = 0; i < strI.length();i++)
                            {
                                pr = (int)str[countObr].toLatin1();
                                pr1 = (int)strI[i].toLatin1();
                                if(pr >= 97) hlp = -32;
                                else hlp = 32;
                                if(pr == pr1 || pr  + hlp == pr1)
                                {
                                    buffer = strI[i];
                                    ui->textEdit->setTextColor(QColor(255,0,0));
                                    ui->textEdit->insertPlainText(buffer);
                                    ui->textEdit->setTextColor(QColor(0,0,0));
                                    if(countObr < str.length() - 1)
                                    {
                                        countObr++;
                                    }
                                    N1++;
                                }
                                else
                                {
                                    buffer = strI[i];
                                    ui->textEdit->insertPlainText(buffer);
                                }
                            }
                            buffer = "";
                            ui->textEdit->append("");
                            QCoreApplication::processEvents();
                            count2++;
                            inter2.setNum(count2);
                            if(count2 == 1) inter2+=" match was found.";
                            else inter2+=" matches were found";
                            if(count2 > 0) ui->label_2->setText(inter2);
                            else ui->label_2->setText("Nothing were found still.");
                        }
                    }
                    // обнуляем все счётчики для следющей итерации цикла с постусловием
                    countObr=0;
                    N1=0;
                    promejF = 0;
                    promej = 0;
                }
            } while(!strI.isNull());
        }
        nFile.close();
        // закрытие файла
        // окончательное заполнение полей вывода результатами обработки файла со словарём
        // результаты поиска по подстроке и посимвольного поиска
        // суммарный результат (total)
        QString setter;// переменная для формирования поля вывода
        setter.setNum(count1);
        if(count1 == 1) setter+=" match was found.";
        else setter+=" matches were found";
        if(count1 > 0) ui->label_3->setText(setter);
        else ui->label_3->setText("Nothing were found.");
        setter.setNum(count2);
        if(count2 == 1) setter+=" match was found.";
        else setter+=" matches were found";
        if(count2 > 0) ui->label_2->setText(setter);
        else ui->label_2->setText("Nothing were found.");
        QString sum;
        setter = "Total: ";
        setter += sum.setNum(count1 + count2);
        if(count1 + count2 == 1) setter += " word.";
        else setter+= " words.";
        ui->label_4->setText(setter);
        ui->label_7->setText("Searching completed.");
        ui->pushButton_2->setEnabled(1);
        ui->pushButton->setEnabled(0);
        ui->lineEdit->setEnabled(0);
    }
    else
    {
        // вывод о некорректно введенных данных
        ui->lineEdit->setText("Incorrect input!");
        ui->pushButton_2->setEnabled(1);
        ui->pushButton->setEnabled(0);
        ui->lineEdit->setEnabled(0);
    }

}
void Widget::on_pushButton_2_clicked()
{
    // кнопка Clear - установка полей "по умолчанию", очищение всех полей вывода
    ui->pushButton_2->setEnabled(0);
    ui->lineEdit->setEnabled(1);
    ui->textEdit->clear();
    ui->textEdit_2->clear();
    ui->label_7->clear();
    ui->label_3->setText("Nothing requested yet.");
    ui->label_2->setText("Nothing requested yet.");
    ui->label_4->clear();
    ui->label_7->clear();
    ui->lineEdit->clear();
    ui->pushButton->setEnabled(1);
}

void Widget::on_pushButton_3_clicked()
{
    // кнопка вывода информационного окна
    dialog.setModal(true);
    dialog.show();
    if(vkl == 0)
    {
        ui->label_8->setText("");
        ui->lineEdit->setEnabled(1);
        ui->pushButton->setEnabled(1);
    }
    vkl = 1;
}

Widget::~Widget()
{
    delete pallete;
    delete ui;
}
