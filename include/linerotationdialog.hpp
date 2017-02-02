#ifndef LINEROTATIONDIALOG_H
#define LINEROTATIONDIALOG_H

#include <QDialog>

#include "mainview.hpp"

namespace Ui {
class lineRotationDialog;
}

class lineRotationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit lineRotationDialog(QWidget *parent = 0, MainView *view = 0);
    ~lineRotationDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::lineRotationDialog *ui;

    MainView *view;
};

#endif // LINEROTATIONDIALOG_H
