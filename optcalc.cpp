/*
 * Расчёт длины регенерационного участка ВОЛС
 */

#include "optcalc.h"
#include "ui_optcalc.h"
#include "qmath.h"

OptCalc::OptCalc(QWidget *parent) : QMainWindow(parent),
                                    ui(new Ui::OptCalc)
{
    ui->setupUi(this);
    this->setRanges();
    this->reset();
}

OptCalc::~OptCalc()
{
    delete ui;
}

// функция устанавливает значения полей ввода по умолчанию
void OptCalc::reset()
{
    this->resetCStyle();
    ui->s_PSpinBox->setValue(1);
    ui->s_LambdaComboBox->setCurrentIndex(0);
    emit ui->s_LambdaComboBox->currentIndexChanged(0);
    ui->s_NuSpinBox->setValue(10);
    ui->s_Tau0SpinBox->setValue(.386);

    ui->l_lsdSpinBox->setValue(5);
    ui->l_nrsSpinBox->setValue(2);
    ui->l_nnsSpinBox->setValue(1);
    ui->l_ArsSpinBox->setValue(.25);
    ui->l_AnsSpinBox->setValue(.1);
    ui->l_MSpinBox->setValue(3);
    ui->l_ADSpinBox->setValue(1);

    ui->r_PSpinBox->setValue(-25);

    ui->c_LSpinBox->setValue(0);
    ui->c_LpdSpinBox->setValue(0);
}

// функция задаёт допустимые диапазоны значений полей ввода
void OptCalc::setRanges()
{
    ui->s_PSpinBox->setRange(-2, 4);
    ui->s_NuSpinBox->setRange(1, 100);
    ui->l_ADSpinBox->setRange(1, 5);
    ui->l_AnsSpinBox->setRange(.1, .25);
    ui->l_ArsSpinBox->setRange(.2, .5);
    ui->l_lsdSpinBox->setRange(1, 10);
    ui->l_MSpinBox->setRange(1, 10);
    ui->l_nrsSpinBox->setMinimum(2);
    ui->r_PSpinBox->setRange(-34, 8);
}

// функция расчёта длины участка регенерации по затуханию
double OptCalc::calcLAlpha()
{
    return (
              ui->s_PSpinBox->value()
            - ui->r_PSpinBox->value()
            - ui->l_nrsSpinBox->value()
            - ui->l_ArsSpinBox->value()
            - ui->l_ADSpinBox->value()
            - ui->l_MSpinBox->value()
           )
           /
           (
             ui->f_AlphaSpinBox->value() * qPow (10, -3)
             +
             (ui->l_AnsSpinBox->value() / (ui->l_lsdSpinBox->value() * qPow(10, 3)))
           )
           * qPow (10, -3);
}

// функция расчёта длины участка регенерации по дисперсии
double OptCalc::calcLD()
{
    return (2 * M_PI * (3 * qPow(10, 8)) * qPow(ui->s_Tau0SpinBox->value() * qPow(10, -9), 2))
           /
           (
             qPow(ui->s_LambdaComboBox->currentText().toInt() * qPow(10, -9), 2)
             *
             ui->f_DSpinBox->value()
             *
             qPow(10, -6)
             *
             sqrt(
               1 + 4 * qPow(M_PI, 2) * qPow(ui->s_NuSpinBox->value() * qPow(10, 9), 2) * qPow(ui->s_Tau0SpinBox->value() * qPow(10, -9), 2)
             )
           ) * qPow(10, -3);
}

// функция изменения значения затухания и дисперсии
// согласно выбранному значению длины волны
void OptCalc::on_s_LambdaComboBox_currentIndexChanged(int index)
{
    ui->f_AlphaSpinBox->setValue(index == 0 ? .36 : .22);
    ui->f_DSpinBox->setValue(index == 0 ? 17 : 3.5);
}

void OptCalc::on_calc_pushButton_clicked()
{
    this->resetCStyle();
    ui->c_LSpinBox->setValue(this->calcLAlpha());
    ui->c_LpdSpinBox->setValue(this->calcLD());
    (ui->c_LSpinBox->value() < ui->c_LpdSpinBox->value() ? ui->c_LSpinBox : ui->c_LpdSpinBox)->setStyleSheet("border: 1px outset green;");
}

void OptCalc::resetCStyle()
{
    ui->c_LSpinBox->setStyleSheet("");
    ui->c_LpdSpinBox->setStyleSheet("");
}

void OptCalc::on_reset_pushButton_clicked()
{
    this->reset();
}
