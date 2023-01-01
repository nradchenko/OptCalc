/*
 * Расчёт длины регенерационного участка ВОЛС
 */

#include "optcalc.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OptCalc w;
    w.show();
    w.setFixedSize(w.size());
    return a.exec();
}
