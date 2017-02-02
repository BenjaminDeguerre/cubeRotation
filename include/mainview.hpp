#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QTimer>
#include <QOpenGLFunctions_4_2_Core>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

#include "glm/glm.hpp"

#include "scene.hpp"

class MainView : public QOpenGLWidget, protected QOpenGLFunctions_4_2_Core
{
    Q_OBJECT

private:
    void loadCube();
    void CreateVBO();

    GLfloat positionDataCube[108];
    GLfloat colorDataCube[108];
    GLfloat positionDataLine[6];
    GLfloat colorDataLine[6];

    QOpenGLBuffer vboHandles[4];
    QOpenGLVertexArrayObject vaoHandle[2];

    int posVertexPosition;
    int posVertexColor;
    int posModelViewMatrix;
    int posMVP;

    int width, height;

    glm::mat4 rotationMatrix;
    glm::mat4 modelCube;
    glm::mat4 view;
    glm::mat4 projection;

    QOpenGLShaderProgram *program;

    QTimer *timer;
    Scene *scene;
    float angle;
    glm::vec3 axis;

public:
    MainView(QWidget *parent = 0 );
    
    void setView(glm::mat4 mview);
    void rotate(float b1, float b2, float b3, float d1, float d2, float d3, float angle);
    void initializeGL();

protected:

    QOpenGLContext *m_context;
    void paintGL();
    void resizeGL(int w, int h);

public slots:
    void timerUpdate();
    void toggleAnimation();
    void takeScreenShot();
};

#endif // MAINVIEW_H
