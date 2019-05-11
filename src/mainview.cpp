#include "mainview.hpp"

#include <fstream>
#include <iostream>

MainView::MainView(QWidget *parent) : QOpenGLWidget(parent) {
  this->setFocusPolicy(Qt::ClickFocus);
  program = new QOpenGLShaderProgram(this);

  timer = new QTimer(this);  // Creating timer for update
  connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
  timer->start(50);
}

MainView::~MainView() {
  delete program;
  delete timer;

  for (int i = 0; i < 2; i++) {
    vaoHandle[i].destroy();
  }

  for (int i = 0; i < 4; i++) {
    vboHandles[i].destroy();
  }
}

void MainView::timerUpdate() {
  // rotation are not queued the new one will erase the previous
  if (rotation) {
    modelCube = rotationMatrix * modelCube;
    count--;
    if (count < 0) {
      count = 0;
      rotation = false;
    }
  }
  update();
}

void MainView::setRotation(float b1, float b2, float b3, float d1, float d2,
                           float d3, float angle) {
  // if axis
  if (!((d1 == d2) && (d2 == d3) && (d3 == 0))) {
    // updating the rotation axis
    positionDataLine[0] = b1 - 2 * d1;
    positionDataLine[1] = b2 - 2 * d2;
    positionDataLine[2] = b3 - 2 * d3;
    positionDataLine[3] = b1 + 2 * d1;
    positionDataLine[4] = b2 + 2 * d2;
    positionDataLine[5] = b3 + 2 * d3;

    // writing to the vao
    vaoHandle[1].bind();
    vboHandles[2].bind();
    vboHandles[2].allocate(positionDataLine, sizeof(positionDataLine));
    vboHandles[2].release();
    vaoHandle[1].release();

    // To set the rotation matrix to one degree in the rigth way
    int angleSign = (angle > 0) - (angle < 0);

    // Setting the boolean value for the update
    this->rotation = true;
    this->count = angle * angleSign;  // count must be positive

    QVector3D tPlus(b1, b2, b3);
    QVector3D tMinus(-b1, -b2, -b3);
    QVector3D axis(d1, d2, d3);

    // creating rotation matrix
    rotationMatrix.setToIdentity();
    rotationMatrix.translate(tMinus);
    rotationMatrix.rotate(angleSign, axis);
    rotationMatrix.translate(tPlus);
  }
}

void MainView::loadCube() {
  std::ifstream ifs("data/sceneCube.dat");

  if (!ifs) {
    std::cout << "data file not found\n";
    exit(1);
  } else {
    for (int i = 0; i < 108; i++) {
      ifs >> positionDataCube[i];
    }
    for (int i = 0; i < 6; i++) {
      ifs >> positionDataLine[i];
    }
    for (int i = 0; i < 108; i++) {
      ifs >> colorDataCube[i];
    }
    for (int i = 0; i < 6; i++) {
      ifs >> colorDataLine[i];
    }
  }
}

void MainView::initializeGL() {
  this->loadCube();
  initializeOpenGLFunctions();

  program->addShaderFromSourceFile(QOpenGLShader::Vertex, "shader/basic.vert");
  program->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                   "shader/basic.frag");

  program->link();
  program->bind();

  // First set of vbo for the cube
  vaoHandle[0].create();  // Might want to check if created for each vao/vbo
  vaoHandle[0].bind();

  posVertexPosition = program->attributeLocation("VertexPosition");
  posVertexColor = program->attributeLocation("VertexColor");
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

  vaoHandle[0].release();

  // Second for the line
  vaoHandle[1].create();
  vaoHandle[1].bind();

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

  vaoHandle[1].release();

  program->release();
  view.lookAt(QVector3D(2.0f, 2.0f, 2.0f), QVector3D(-2.0f, -2.0f, -2.0f),
              QVector3D(0.0f, 1.0f, 0.0f));
  glClearColor(0, 0, 0, 1);
  glEnable(GL_DEPTH_TEST);
}

void MainView::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  program->bind();
  vaoHandle[0].bind();

  program->setUniformValue(posMVP, projection * view * modelCube);
  glDrawArrays(GL_TRIANGLES, 0, 36);

  vaoHandle[0].release();

  vaoHandle[1].bind();

  program->setUniformValue(posMVP, projection * view);
  glDrawArrays(GL_LINES, 0, 2);

  vaoHandle[1].release();
  program->release();
}

void MainView::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  projection.setToIdentity();
  projection.perspective(30, (float)w / h, 0.3f, 30.0f);
}

void MainView::setView(QMatrix4x4 mview) {
  view = mview;
  update();
}
