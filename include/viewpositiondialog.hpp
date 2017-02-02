#ifndef VIEWPOSITIONDIALOG_H
#define VIEWPOSITIONDIALOG_H

#include "mainview.hpp"

#include <QDialog>


namespace Ui {
class viewPositionDialog;
}

class viewPositionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit viewPositionDialog(QWidget *parent = 0, MainView *view = 0);
    ~viewPositionDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::viewPositionDialog *ui;

    MainView *view;
};

#endif // VIEWPOSITIONDIALOG_H
