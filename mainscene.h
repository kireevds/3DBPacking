#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QTimer>
#include <QGLWidget>
#include <QPoint>
#include <QDebug>
#include <QMouseEvent>
#include <container.h>

class MainScene : public QGLWidget
{
    Q_OBJECT

private:
    GLfloat cubeVertexArray[8][3];
    GLfloat cubeColorArray[8][3];
    GLubyte cubeIndexArray[6][4];
    GLubyte cubeEdgesIndexArray[12][2];

    GLfloat contVertexArray[8][3];
    GLfloat contColorArray[8][3];

    QPoint pressPosition;
    QPoint releasePosition;
    GLfloat xAxisRotation;
    GLfloat yAxisRotation;
    GLfloat currentWidth;
    GLfloat currentHeight;

    int xlength;
    int ylength;
    int zlength;
    Container* workContainer; //обрабатываемый контейнер
    QVector<float>* clrs;
    bool iscontainer;

protected:
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);



public:
    MainScene(QWidget *parent = 0);
    void setParameters(Container* wC);
    ~MainScene();

};

#endif // MAINSCENE_H
