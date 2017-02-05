#include "mainwindow.hpp"
#include "mainview.hpp"

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow *window = new MainWindow();


    QWidget* win = new QWidget(window);

    QSurfaceFormat format;
    format.setVersion(4,2); //To change depending on the openGL to use
    format.setProfile(QSurfaceFormat::CoreProfile); //Same

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
