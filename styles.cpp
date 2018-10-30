#include "Calculator.h"


void Calculator::setStyles()
{
    /*
     * Main widget styles:
     */
    this->setStyleSheet(
                "QWidget {\n"
                "  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
                "                    stop: 0 #383EB5, stop: 1 #070929);\n"
                "  border: 1px solid gray;\n"
                "}\n"
                );


    /*
     * QLCDNumber widget styles:
     */
    lcd->setStyleSheet(
                "QWidget {\n"
                "  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
                "                    stop: 0 #20A389, stop: 1 #266155);\n"
                "  border: 1px solid gray;\n"
                "}\n"
                );

    /*
     * QPushButton styles:
     */
    QPushButton* need = nullptr;
    QObjectList list = this->children();
    for (QObjectList::iterator it = list.begin(); it != list.end() ; ++it)
    {
        need = qobject_cast<QPushButton*>(*it);
        if (need)
        {
            if (need->text().contains(QRegExp("[\\-*/+X]")) )
            {
                need->setStyleSheet(
                            "QPushButton {\n"
                            "  background-color: rgb(255, 151, 57);\n"
                            "  color: white; \n"
                            "  border: 1px solid gray;\n"
                            "}\n"
                            "QPushButton:pressed {\n"
                            "  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
                            "                    stop: 0 #FF7832, stop: 1 #FF9739);\n"
                            "}"
                            );
            }
            else if (need->text().contains(QRegExp("[0-9(CE)=\\.]")) )
            {
                need->setStyleSheet(
                            "QPushButton {\n"
                            "  background-color: rgb(62, 62, 71);\n"
                            "  color: white; \n"
                            "  border: 1px solid gray;\n"
                            "}\n"
                            "QPushButton:pressed {\n"
                            "  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
                            "                    stop: 0 #626269, stop: 1 #A8A8A8);\n"
                            "}"
                            );
            }
        }
    }



}
