#include "mainview.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <cstdio>

const double PI = 4.0*atan(1.0);

MainView::MainView(QWidget *parent) : QOpenGLWidget(parent)
{
    // This tells the widget to accept keyboard focus when the widget is clicked.

    this->setFocusPolicy(Qt::ClickFocus);
//    timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
//    timer->start(50);
    program = new QOpenGLShaderProgram(this);

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




//    vboHandles[0].bind();

//    vboHandles[0].release();

//    vboHandles[1].bind();

//    vboHandles[1].release();

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


    view = glm::lookAt(glm::vec3(2.0f,2.0f,2.0f), glm::vec3(-2.0f,-2.0f,-2.0f), glm::vec3(0.0f,1.0f,0.0f));
    projection = glm::mat4(1.0f);
    modelCube = glm::mat4(1.0f);
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
}

void MainView::paintGL() {
    makeCurrent();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 mv =  view * modelCube;
    vaoHandle[0].bind();
    program->bind();

    QMatrix4x4 mvq = QMatrix4x4(glm::value_ptr(mv)).transposed();
    QMatrix4x4 mvp =  QMatrix4x4(glm::value_ptr(projection)).transposed()*QMatrix4x4(glm::value_ptr(mv)).transposed();
    program->setUniformValue(posModelViewMatrix, mvq);
    program->setUniformValue(posMVP, mvp);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    program->release();
    vaoHandle[0].release();

//    vaoHandle[1].bind();
//    program->bind();

//    mvq = QMatrix4x4(glm::value_ptr(view)).transposed();
//    mvp =  QMatrix4x4(glm::value_ptr(projection)).transposed()*QMatrix4x4(glm::value_ptr(view)).transposed();
//    program->setUniformValue(posModelViewMatrix, mvq);
//    program->setUniformValue(posMVP, mvp);
//    glDrawArrays(GL_LINE, 0, 6);
//    program->release();
//    vaoHandle[1].release();
    //QOpenGLContext::currentContext()->swapBuffers(this);
//    std::cout << "fdjksf" << std::endl;
//    mv = view;
//    //program->setUniformValue(modelViewMatrix, QMatrix4x4(glm::value_ptr(mv)));
//    program->setUniformValue(posMVP, QMatrix4x4(glm::value_ptr(projection)) * QMatrix4x4(glm::value_ptr(mv)));
//    glBindVertexArray(vaoHandle[1]);
//    glDrawArrays(GL_LINES, 0, 6);
}

void MainView::resizeGL(int w, int h ) {
    glViewport(0,0,w,h);
    width = w;
    height = h;
    projection = glm::perspective((float)PI/6, (float)w/h, 0.3f, 30.0f);
}

void MainView::takeScreenShot() {
    //QImage img = this->grabFrameBuffer(true);
    //img.save("screen.png", "PNG");
}

void MainView::toggleAnimation() {
    if( timer->isActive() )
        timer->stop();
    else
        timer->start();
}

void MainView::timerUpdate() {
//    angle += t*2*PI/360.0;
//    if( t >= 360.0) angle -= 360.0;
   // paintGL();
}

void MainView::setView(glm::mat4 mview)
{
    view = mview;
    paintGL();
}

 void MainView::rotate(float b1, float b2, float b3, float d1, float d2, float d3, float angle){

     float angleRad = ((0 <= angle) - (angle < 0)) * 2 * 4.0*atan(1.0) / 360;

     float norm = sqrt(d1*d1+d2*d2+d3*d3);
     float x = d1 / norm, y = d2 / norm, z = d3 /norm;
     float cosa = cos(angleRad);
     float sina = sin(angleRad);

     glm::mat4 t1(1.0f), t2(1.0f), rot(1.0f);

     if (!((d1 == d2) && (d2 == d3) && (d3 == 0))) {
         // Translation matrix
         t1[3][0] = -b1;
         t1[3][1] = -b2;
         t1[3][2] = -b3;

         // We could use -t1 but the result is not as smooth
         t2[3][0] = b1;
         t2[3][1] = b2;
         t2[3][2] = b3;

         // Rotation matrix between the two translation (from origin)
         rot[0][0] = (1-cosa)*x*x + cosa;
         rot[0][1] = (1-cosa)*x*y + sina * z;
         rot[0][2] = (1-cosa)*x*z - sina * y;
         rot[1][0] = (1-cosa)*x*y - sina * z;
         rot[1][1] = (1-cosa)*y*y + cosa;
         rot[1][2] = (1-cosa)*y*z + sina * x;
         rot[2][0] = (1-cosa)*x*z + sina * y;
         rot[2][1] = (1-cosa)*z*y - sina * x;
         rot[2][2] = (1-cosa)*z*z + cosa;

         // Final matrix for the rotation
         rotationMatrix = t2*rot*t1;

         positionDataLine[0] = b1 - 2 *d1;
         positionDataLine[1] = b2 - 2 *d2;
         positionDataLine[2] = b3 - 2 *d3;
         positionDataLine[3] = b1 + 2 * d1;
         positionDataLine[4] = b2 + 2 * d2;
         positionDataLine[5] = b3 + 2 * d3;
         vaoHandle[1].bind();
         vboHandles[2].bind();
         vboHandles[2].write(0,positionDataLine,sizeof(positionDataLine));
         vboHandles[2].release();
         vaoHandle[1].release();
         //glBufferSubData(GL_ARRAY_BUFFER, 0, 6*sizeof(float), positionDataLine);
         for (int i = 0 ; i < angle * ((0 <= angle) - (angle < 0)) ; i++) {
             modelCube = rotationMatrix * modelCube;
             paintGL();
         }
     }
 }
