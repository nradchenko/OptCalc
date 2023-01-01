/*
 * Расчёт длины регенерационного участка ВОЛС
 */

#ifndef OPTCALC_H
#define OPTCALC_H

#include <QMainWindow>

namespace Ui
{
    class OptCalc;
}

class OptCalc : public QMainWindow
{
    Q_OBJECT

public:
    explicit OptCalc(QWidget *parent = 0);
    ~OptCalc();

private slots:
    void on_s_LambdaComboBox_currentIndexChanged(int);
    void on_reset_pushButton_clicked();
    void on_calc_pushButton_clicked();

private:
    Ui::OptCalc *ui;
    void reset();
    void setRanges();
    double calcLAlpha();
    double calcLD();
    void resetCStyle();
};

#endif // OPTCALC_H
