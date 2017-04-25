#include "mainscene.h"
#include <math.h>
#include <glext.h>
#include <gl.h>

MainScene::MainScene(QWidget *parent):QGLWidget(parent)
{
    xAxisRotation = yAxisRotation = 0;
    xlength = 1;
    ylength = 1;
    zlength = 1;
    clrs = new QVector<float>;
    clrs->append(0.0f);
    clrs->append(0.2f);
    clrs->append(0.4f);
    clrs->append(0.6f);
    clrs->append(0.8f);
    clrs->append(1.0f); //6 наиболее отличимых оттенов красного, зеленого и синего
    iscontainer = false;
}

MainScene::~MainScene()
{

}

void MainScene::initializeGL()
{
    glClearColor(0.9254, 0.9254, 0.9254, 1.0);

    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    glEnable(GL_CULL_FACE);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
}

void MainScene::resizeGL(int nWidth, int nHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-(xlength+xlength/5), (xlength+xlength/5), -(ylength+ylength/5), (ylength+ylength/5), -(zlength+zlength/5), (zlength+zlength/5)); //РАССЧИТАТЬ по правилам поворота
    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
    currentWidth = nWidth;
    currentHeight = nHeight;
}


void MainScene::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glRotatef(yAxisRotation, 0.0, 1.0, 0.0);
    glRotatef(xAxisRotation, 1.0, 0.0, 0.0);

    if(iscontainer)
    {
        float xx = -xlength/(float)2;
        float yy = -ylength/(float)2;
        float zz = -zlength/(float)2;

        //Отрисовка контейнера
        contVertexArray[0][0] = xx;
        contVertexArray[0][1] = zz;
        contVertexArray[0][2] = yy;

        contVertexArray[1][0] = xx+xlength;
        contVertexArray[1][1] = zz;
        contVertexArray[1][2] = yy;

        contVertexArray[2][0] = xx+xlength;
        contVertexArray[2][1] = zz;
        contVertexArray[2][2] = yy+ylength;

        contVertexArray[3][0] = xx;
        contVertexArray[3][1] = zz;
        contVertexArray[3][2] = yy+ylength;

        contVertexArray[4][0] = xx;
        contVertexArray[4][1] = zz+zlength;
        contVertexArray[4][2] = yy;

        contVertexArray[5][0] = xx+xlength;
        contVertexArray[5][1] = zz+zlength;
        contVertexArray[5][2] = yy;

        contVertexArray[6][0] = xx+xlength;
        contVertexArray[6][1] = zz+zlength;
        contVertexArray[6][2] = yy+ylength;

        contVertexArray[7][0] = xx;
        contVertexArray[7][1] = zz+zlength;
        contVertexArray[7][2] = yy+ylength;

        for (int j = 0; j<7; j++)
        {
            contColorArray[j][0] = 0.0;
            contColorArray[j][1] = 0.0;
            contColorArray[j][2] = 0.0;
        }

        cubeEdgesIndexArray[0][0] = 0;
        cubeEdgesIndexArray[0][1] = 3;
        cubeEdgesIndexArray[1][0] = 0;
        cubeEdgesIndexArray[1][1] = 4;
        cubeEdgesIndexArray[2][0] = 0;
        cubeEdgesIndexArray[2][1] = 1;
        cubeEdgesIndexArray[3][0] = 1;
        cubeEdgesIndexArray[3][1] = 2;
        cubeEdgesIndexArray[4][0] = 1;
        cubeEdgesIndexArray[4][1] = 5;
        cubeEdgesIndexArray[5][0] = 5;
        cubeEdgesIndexArray[5][1] = 4;
        cubeEdgesIndexArray[6][0] = 6;
        cubeEdgesIndexArray[6][1] = 5;
        cubeEdgesIndexArray[7][0] = 6;
        cubeEdgesIndexArray[7][1] = 7;
        cubeEdgesIndexArray[8][0] = 6;
        cubeEdgesIndexArray[8][1] = 2;
        cubeEdgesIndexArray[9][0] = 4;
        cubeEdgesIndexArray[9][1] = 7;
        cubeEdgesIndexArray[10][0] = 3;
        cubeEdgesIndexArray[10][1] = 7;
        cubeEdgesIndexArray[11][0] = 3;
        cubeEdgesIndexArray[11][1] = 2;

        glLineWidth(2);
        glVertexPointer(3, GL_FLOAT, 0, contVertexArray);
        glColorPointer(3, GL_FLOAT, 0, contColorArray);
        glDrawElements(GL_LINES, 24, GL_UNSIGNED_BYTE, cubeEdgesIndexArray);

    for(int i=0; i< workContainer->myobjects->size(); i++)
    {
        float w = workContainer->myobjects->at(i)->width;
        float l = workContainer->myobjects->at(i)->length;
        float h = workContainer->myobjects->at(i)->height;
        float x = workContainer->myobjects->at(i)->x - xlength/2;
        float y = workContainer->myobjects->at(i)->y - ylength/2;
        float z = workContainer->myobjects->at(i)->z - zlength/2;

        cubeVertexArray[0][0] = x; //x
        cubeVertexArray[0][1] = z; //z
        cubeVertexArray[0][2] = y+l; //y

        cubeVertexArray[1][0] = x;
        cubeVertexArray[1][1] = z+h;
        cubeVertexArray[1][2] = y+l;

        cubeVertexArray[2][0] = x+w;
        cubeVertexArray[2][1] = z+h;
        cubeVertexArray[2][2] = y+l;

        cubeVertexArray[3][0] = x+w;
        cubeVertexArray[3][1] = z;
        cubeVertexArray[3][2] = y+l;

        cubeVertexArray[4][0] = x;
        cubeVertexArray[4][1] = z;
        cubeVertexArray[4][2] = y;

        cubeVertexArray[5][0] = x;
        cubeVertexArray[5][1] = z+h;
        cubeVertexArray[5][2] = y;

        cubeVertexArray[6][0] = x+w;
        cubeVertexArray[6][1] = z+h;
        cubeVertexArray[6][2] = y;

        cubeVertexArray[7][0] = x+w;
        cubeVertexArray[7][1] = z;
        cubeVertexArray[7][2] = y;

        float r = clrs->at(rand()%(clrs->size()-1));
        float g = clrs->at(rand()%(clrs->size()-1));
        float b = clrs->at(rand()%(clrs->size()-1));
        for (int j = 0; j<7; j++)
        {
            cubeColorArray[j][0] = r;
            cubeColorArray[j][1] = g;
            cubeColorArray[j][2] = b;
        }

        cubeIndexArray[0][0] = 0;
        cubeIndexArray[0][1] = 3;
        cubeIndexArray[0][2] = 2;
        cubeIndexArray[0][3] = 1;

        cubeIndexArray[1][0] = 0;
        cubeIndexArray[1][1] = 1;
        cubeIndexArray[1][2] = 5;
        cubeIndexArray[1][3] = 4;

        cubeIndexArray[2][0] = 7;
        cubeIndexArray[2][1] = 4;
        cubeIndexArray[2][2] = 5;
        cubeIndexArray[2][3] = 6;

        cubeIndexArray[3][0] = 3;
        cubeIndexArray[3][1] = 7;
        cubeIndexArray[3][2] = 6;
        cubeIndexArray[3][3] = 2;

        cubeIndexArray[4][0] = 1;
        cubeIndexArray[4][1] = 2;
        cubeIndexArray[4][2] = 6;
        cubeIndexArray[4][3] = 5;

        cubeIndexArray[5][0] = 0;
        cubeIndexArray[5][1] = 4;
        cubeIndexArray[5][2] = 7;
        cubeIndexArray[5][3] = 3;

        glVertexPointer(3, GL_FLOAT, 0, cubeVertexArray);
        glColorPointer(3, GL_FLOAT, 0, cubeColorArray);
        glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndexArray);

        glLineWidth(1);
        glVertexPointer(3, GL_FLOAT, 0, cubeVertexArray);
        glColorPointer(3, GL_FLOAT, 0, contColorArray);
        glDrawElements(GL_LINES, 24, GL_UNSIGNED_BYTE, cubeEdgesIndexArray);
    }
    }
}

void MainScene::mousePressEvent(QMouseEvent *event)
{
    pressPosition = event->pos();
}

void MainScene::mouseMoveEvent(QMouseEvent *event)
{
    xAxisRotation += (180 * ((GLfloat)event->y() - (GLfloat)pressPosition.y())) / (currentHeight);
    yAxisRotation += (180 * ((GLfloat)event->x() - (GLfloat)pressPosition.x())) / (currentWidth);

    pressPosition = event->pos();

    updateGL();
}

void MainScene::setParameters(Container* wC)
{
    workContainer = wC;
    xlength = workContainer->width;
    ylength = workContainer->length;
    zlength = workContainer->height;
    iscontainer = true;
    resizeGL(280,280); //Костыль. Мне нужно изменить видимую часть координатной оси (glOrtho) под размеры выбранного контейнера.
    updateGL();
}
