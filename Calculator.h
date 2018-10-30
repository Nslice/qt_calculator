#pragma once
#ifndef MY_CALCULATOR_H
#define MY_CALCULATOR_H

#include <QtWidgets>
#include <QStack>



class Calculator : public QWidget
{
    Q_OBJECT
private:
    QLCDNumber* lcd;
    QStack<QString> stkVal;
    QString sVal;

public:
    explicit Calculator(QWidget* parent = nullptr);
    ~Calculator() {}

private:
    void setStyles(); //просто чтобы отделить настройку стилей от конструктора
    double calculate();

private slots:
    void slotButtonClicked();
};

#endif //MY_CALCULATOR_H
