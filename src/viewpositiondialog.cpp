#include "viewpositiondialog.hpp"
#include "ui_viewpositiondialog.h"
#include "mainview.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

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
    float directx = ui->lineEdit_4->text().toFloat();
    float directy = ui->lineEdit_5->text().toFloat();
    float directz = ui->lineEdit_6->text().toFloat();

    view->setView(glm::lookAt(glm::vec3(eyex, eyey, eyez),
                              glm::vec3(eyex + directx, eyey + directy, eyez + directz),
                              glm::vec3(0.0f,1.0f,0.0f)));
    this->done(0);
}
