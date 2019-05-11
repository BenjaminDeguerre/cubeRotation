#include "viewpositiondialog.hpp"
#include "ui_viewpositiondialog.h"

viewPositionDialog::viewPositionDialog(QWidget *parent, MainView *view) :
    QDialog(parent),
    ui(new Ui::viewPositionDialog)
{
    ui->setupUi(this);
    this->view = view;
}

viewPositionDialog::~viewPositionDialog()
{
    delete ui;
}

void viewPositionDialog::on_pushButton_clicked()
{
    float eyex = ui->lineEdit->text().toFloat();
    float eyey = ui->lineEdit_2->text().toFloat();
    float eyez = ui->lineEdit_3->text().toFloat();
    float x = ui->lineEdit_4->text().toFloat();
    float y = ui->lineEdit_5->text().toFloat();
    float z = ui->lineEdit_6->text().toFloat();

    QMatrix4x4 mview;
    mview.lookAt(QVector3D(eyex, eyey, eyez),
                 QVector3D(x, y, z),
                 QVector3D(0.0,1.0,0.0));
    view->setView(mview);
    this->done(0);
}
