#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "glm/gtc/matrix_transform.hpp"
#include "linerotationdialog.hpp"
#include "viewpositiondialog.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::setView(MainView *view)
{
    this->view = view;
    //this->view->initializeGL();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSetLineRotation_triggered()
{
    lineRotationDialog mDialog(0,this->view);
    mDialog.setModal((true));
    mDialog.exec();
}

void MainWindow::on_actionSetView_triggered()
{
    viewPositionDialog mDialog(0,this->view);
    mDialog.setModal((true));
    mDialog.exec();
}

void MainWindow::on_actionSetDefaultView_triggered()
{
    view->setView(glm::lookAt(glm::vec3(0.0f,0.0f,2.0f), glm::vec3(0.0f,0.0f,-1.0f), glm::vec3(0.0f,1.0f,0.0f)));
}
