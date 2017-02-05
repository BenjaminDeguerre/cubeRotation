#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QTimer>
#include <QOpenGLFunctions_4_2_Core>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

class MainView : public QOpenGLWidget, protected QOpenGLFunctions_4_2_Core
{
    Q_OBJECT

private:

    void loadCube();

    GLfloat positionDataCube[108];
    GLfloat colorDataCube[108];
    GLfloat positionDataLine[6];
    GLfloat colorDataLine[6];

    QOpenGLBuffer vboHandles[4];
    QOpenGLVertexArrayObject vaoHandle[2];

    int posVertexPosition;
    int posVertexColor;
    int posMVP;

    float count;
    bool rotation;


    QMatrix4x4 rotationMatrix;
    QMatrix4x4 modelCube;
    QMatrix4x4 view;
    QMatrix4x4 projection;

    QTimer *timer;
    QOpenGLShaderProgram *program;

public:
    MainView(QWidget *parent = 0 );
    ~MainView();
    void setView(QMatrix4x4 mview);
    void rotate(float b1, float b2, float b3, float d1, float d2, float d3, float angle);
    void initializeGL();
    void setRotation(float b1, float b2, float b3, float d1, float d2, float d3, float angle);

protected:
    void paintGL();
    void resizeGL(int w, int h);

public slots:
    void timerUpdate();
};

#endif // MAINVIEW_H
