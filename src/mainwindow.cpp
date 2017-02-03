#include "mainwindow.hpp"
#include "ui_mainwindow.h"
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
    QMatrix4x4 m_view;
    m_view.lookAt(QVector3D(0.0,0.0,2.0), QVector3D(0.0f,0.0f,-1.0f), QVector3D(0.0f,1.0f,0.0f));
    view->setView(m_view);
}
