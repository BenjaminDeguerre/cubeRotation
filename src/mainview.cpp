#include "mainview.hpp"

#include <QThread>

#include <fstream>
#include <iostream>
#include <cstdio>

const double PI = 4.0*atan(1.0);

MainView::MainView(QWidget *parent) : QOpenGLWidget(parent)
{
    this->setFocusPolicy(Qt::ClickFocus);
    program = new QOpenGLShaderProgram(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
    timer->start(50);
}

MainView::~MainView() {
    delete program;

    vaoHandle[0].destroy();
    vaoHandle[1].destroy();
}

void MainView::timerUpdate() {

    if(rotation){

        modelCube = rotationMatrix * modelCube;
        count--;
        if(count < 0){
            count = 0;
            rotation = false;
        }
    }
    update();
}

void MainView::setRotation(float b1, float b2, float b3, float d1, float d2, float d3, float angle){
    if (!((d1 == d2) && (d2 == d3) && (d3 == 0))) {

        positionDataLine[0] = b1 - 2 *d1;
        positionDataLine[1] = b2 - 2 *d2;
        positionDataLine[2] = b3 - 2 *d3;
        positionDataLine[3] = b1 + 2 * d1;
        positionDataLine[4] = b2 + 2 * d2;
        positionDataLine[5] = b3 + 2 * d3;
        vaoHandle[1].bind();
        vboHandles[2].bind();
        vboHandles[2].allocate(positionDataLine,sizeof(positionDataLine));
        vboHandles[2].release();
        vaoHandle[1].release();

        int angleSign = (angle > 0)-(angle < 0);

        this->rotation = true;
        this->count = angle * angleSign;

        this->tPlus.setX(b1);
        this->tPlus.setY(b2);
        this->tPlus.setZ(b3);

        this->tMoins.setX(-b1);
        this->tMoins.setY(-b2);
        this->tMoins.setZ(-b3);

        this->axis.setX(d1);
        this->axis.setY(d2);
        this->axis.setZ(d3);
        this->angle = angleSign;

        rotationMatrix.setToIdentity();
        rotationMatrix.translate(this->tMoins);
        rotationMatrix.rotate(this->angle, this->axis);
        rotationMatrix.translate(this->tPlus);
    }
}

void MainView::loadCube() {
    std::ifstream ifs("../../data/sceneCube.dat");

    if (!ifs) {
        std::cout << "data file not found\n";
        exit(1);
    } else {
        for (int i=0; i<108; i++) {
            ifs >> positionDataCube[i];
        }
        for (int i=0; i<6; i++){
            ifs >> positionDataLine[i];
        }
        for (int i=0; i<108; i++) {
            ifs >> colorDataCube[i];
        }
        for (int i=0; i<6; i++) {
            ifs >> colorDataLine[i];
        }
    }
}

void MainView::initializeGL() {

    this->loadCube();
    initializeOpenGLFunctions();

    program->addShaderFromSourceCode(QOpenGLShader::Vertex,"#version 400\n"
                                   "in vec3 VertexPosition;\n"
                                   "in vec3 VertexColor;\n"
                                   "out vec3 Color;\n"
                                   "uniform mat4 ModelViewMatrix;"
                                   "uniform mat4 MVP;\n"
                                   "void main()\n"
                                   "{\n"
                                   "Color = VertexColor;\n"
                                   "gl_Position = MVP * vec4(VertexPosition,1.0);\n"
                                   "}\n");

    program->addShaderFromSourceCode(QOpenGLShader::Fragment,"#version 330\n"
                                                             "in vec3 Color;\n"
                                                             "out vec4 FragColor;\n"
                                                             "void main() {\n"
                                                             "FragColor = vec4(Color, 1.0);\n"
                                                             "}\n");


    program->link();

    vaoHandle[0].create();
    if (vaoHandle[0].isCreated()){
        vaoHandle[0].bind();
    }


    program->bind();
    posVertexPosition = program->attributeLocation("VertexPosition");
    posVertexColor = program->attributeLocation("VertexColor");
    posModelViewMatrix = program->uniformLocation("ModelViewMatrix");
    posMVP = program->uniformLocation("MVP");

    vboHandles[0].create();
    vboHandles[0].setUsagePattern(QOpenGLBuffer::StaticDraw);
    vboHandles[0].bind();
    vboHandles[0].allocate(positionDataCube, sizeof(positionDataCube));
    program->enableAttributeArray(posVertexPosition);
    program->setAttributeBuffer(posVertexPosition, GL_FLOAT, 0, 3);
    vboHandles[0].release();

    vboHandles[1].create();
    vboHandles[1].setUsagePattern(QOpenGLBuffer::StaticDraw);
    vboHandles[1].bind();
    vboHandles[1].allocate(colorDataCube, sizeof(colorDataCube));
    program->enableAttributeArray(posVertexColor);
    program->setAttributeBuffer(posVertexColor, GL_FLOAT, 0, 3);
    vboHandles[1].release();


    program->release();

    vaoHandle[0].release();

    vaoHandle[1].create();
    if (vaoHandle[1].isCreated()){
        vaoHandle[1].bind();
    }


    program->bind();

    vboHandles[2].create();
    vboHandles[2].setUsagePattern(QOpenGLBuffer::DynamicDraw);
    vboHandles[2].bind();
    vboHandles[2].allocate(positionDataLine, sizeof(positionDataLine));
    program->enableAttributeArray(posVertexPosition);
    program->setAttributeBuffer(posVertexPosition, GL_FLOAT, 0, 3);
    vboHandles[2].release();

    vboHandles[3].create();
    vboHandles[3].setUsagePattern(QOpenGLBuffer::StaticDraw);
    vboHandles[3].bind();
    vboHandles[3].allocate(colorDataLine, sizeof(colorDataLine));
    program->enableAttributeArray(posVertexColor);
    program->setAttributeBuffer(posVertexColor, GL_FLOAT, 0, 3);
    vboHandles[3].release();

    program->release();
    vaoHandle[1].release();


    view.lookAt(QVector3D(2.0f,2.0f,2.0f), QVector3D(-2.0f,-2.0f,-2.0f), QVector3D(0.0f,1.0f,0.0f));
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
}

void MainView::paintGL() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    QMatrix4x4 mv =  view * modelCube;
    vaoHandle[0].bind();
    program->bind();

    QMatrix4x4 mvq = mv;
    QMatrix4x4 mvp =  projection * mv;
    program->setUniformValue(posModelViewMatrix, mvq);
    program->setUniformValue(posMVP, mvp);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    program->release();
    vaoHandle[0].release();

    vaoHandle[1].bind();
    program->bind();

    QMatrix4x4 mvp2 =  projection * view;
    program->setUniformValue(posModelViewMatrix, view);
    program->setUniformValue(posMVP, mvp2);
    glDrawArrays(GL_LINES, 0, 2);
    program->release();
    vaoHandle[1].release();
//    update();
}

void MainView::resizeGL(int w, int h ) {
    glViewport(0,0,w,h);
    width = w;
    height = h;
    projection.setToIdentity();
    projection.perspective(30, (float)w/h, 0.3f, 30.0f);
}

void MainView::setView(QMatrix4x4 mview)
{
    view = mview;
    paintGL();
}
