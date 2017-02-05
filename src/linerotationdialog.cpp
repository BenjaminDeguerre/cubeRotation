#include "linerotationdialog.hpp"
#include "ui_linerotationdialog.h"

lineRotationDialog::lineRotationDialog(QWidget *parent, MainView *view):
    QDialog(parent),
    ui(new Ui::lineRotationDialog)
{
    ui->setupUi(this);
    this->view = view;
}

lineRotationDialog::~lineRotationDialog()
{
    delete ui;
}

void lineRotationDialog::on_pushButton_clicked()
{
    float b1 = ui->lineEdit->text().toFloat();
    float b2 = ui->lineEdit_2->text().toFloat();
    float b3 = ui->lineEdit_3->text().toFloat();
    float d1 = ui->lineEdit_4->text().toFloat();
    float d2 = ui->lineEdit_5->text().toFloat();
    float d3 = ui->lineEdit_6->text().toFloat();
    float angle = ui->lineEdit_7->text().toFloat();

    this->hide();

    view->setRotation(b1,  b2,  b3,  d1,  d2,  d3, angle);

    this->done(0);

}
