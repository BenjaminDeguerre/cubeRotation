#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "mainview.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setView(MainView* view);
    ~MainWindow();

private slots:
    void on_actionSetLineRotation_triggered();

    void on_actionSetView_triggered();

    void on_actionSetDefaultView_triggered();

private:
    Ui::MainWindow *ui;
    MainView* view;
};

#endif // MAINWINDOW_H
