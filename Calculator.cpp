#include "Calculator.h"


Calculator::Calculator(QWidget* parent) : QWidget(parent)
{
    /*
      лямбда для создания и соединения кнопок,
      (чтобы не забивать пространство имен, ведь создание кнопок
      будет использоваться только в конструкторе)
     */
    std::function <QPushButton* (const QString&)> createButton;
    createButton = [this](const QString& str) -> QPushButton*
    {
        QPushButton* pcmd = new QPushButton(str);
        pcmd->setMinimumSize(40, 40);
        connect(pcmd, &QPushButton::clicked, this, &Calculator::slotButtonClicked);
        return pcmd;
    };

    /*
     * Инициализация:
     */
    lcd = new QLCDNumber(12);
    lcd->setSegmentStyle(QLCDNumber::Flat);
    lcd->setMinimumSize(150, 50);

    QChar aButtons[4][4] = {{'7', '8', '9', '/'},
                            {'4', '5', '6', '*'},
                            {'1', '2', '3', '-'},
                            {'0', '.', '=', '+'}
                           };
    //Layout setup
    QGridLayout* gridLayout = new QGridLayout;
    gridLayout->addWidget(lcd, 0, 0, 1, 4);
    gridLayout->addWidget(createButton("CE"), 1, 2);
    gridLayout->addWidget(createButton("X"), 1, 3);

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            gridLayout->addWidget(createButton(aButtons[i][j]), i + 2, j);

    gridLayout->setSpacing(0);
    gridLayout->setVerticalSpacing(2);


    this->setLayout(gridLayout);

    // стили гавно, потом надо переделать
    this->setStyles(); //установка стилей в файле style.cpp
}



double Calculator::calculate()
{
    double  operand2 = stkVal.pop().toDouble();
    QString strOperation = stkVal.pop();
    double  operand1 = stkVal.pop().toDouble();
    double  result = 0;

    if (strOperation == "+")
        result = operand1 + operand2;
    else if (strOperation == "-")
        result = operand1 - operand2;
    else if (strOperation == "/")
        result = operand1 / operand2;
    else if (strOperation == "*")
        result = operand1 * operand2;

    return result;
}



void Calculator::slotButtonClicked()
{

    QString str = qobject_cast<QPushButton*>(sender())->text();

    if (str == "CE")  // сброс всего
    {
        stkVal.clear();
        sVal.clear();
        lcd->display(0);
        return;
    }


    if (str.contains(QRegExp("[0-9]"))) // ввод циффр
    {
        sVal += str;
        lcd->display(sVal.toDouble());
    }
    else if (str == ".")
    {
        if (!sVal.contains('.')) // чтобы не было больше 1 точки
        {
            sVal += str;
            lcd->display(sVal);
        }
    }
    else if (str == "X")   // удаления последней цифры из числа
    {
        if (sVal.isEmpty()) return;
        sVal.remove(sVal.size() - 1, 1);
        lcd->display(sVal.toDouble());
    }
    else // нажатие кнокпок арфм. операций:
    {
        if (stkVal.size() >= 2) // после ввода 2 операнда и знака (+,-,*,/,=)
        {
            stkVal.push(sVal);
            sVal = QString::number(calculate(), 'g', 12); // в строку с точностью 12 символов после точки
            lcd->display(sVal.toDouble());
            //после calculate() стек очиститься

            // если идет цепочка арфм. операций, то после очистки стека
            // результат прошлой операции заносится в стек, а за ним символ операции.
            if (str != "=")
            {
                stkVal.push(sVal);    // помещение результата
                stkVal.push(str);
                sVal.clear();         // очистка строки для ввода
            }

            // если же для показа результата была нажата '=', то стек остается пустым,
            // но строка sVal хранит текущее значение и попадет в стек вместе с символом операции,
            // при нажатии на арфм. операцию.
        }
        else
        {
            stkVal.push(sVal); // добавить первый операнд
            stkVal.push(str);  // добавить знак арфм. оперции
            sVal.clear();
            lcd->display(0);
        }
    }

}
