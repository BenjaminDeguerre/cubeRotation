#include "mainwindow.hpp"
#include "mainview.hpp"

#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QMainWindow>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow *window = new MainWindow();


    QWidget* win = new QWidget(window);

    QSurfaceFormat format;
    format.setVersion(4,2);
    format.setProfile(QSurfaceFormat::CoreProfile);

    MainView *glView = new MainView(window);
    glView->setFormat(format);
    window->setView(glView);

    QVBoxLayout *mainLayout = new QVBoxLayout(win);
    mainLayout->addWidget(glView);
    window->setCentralWidget(win);

    window->setWindowTitle("Cube Rotation");
    window->show();
    return app.exec();
}
