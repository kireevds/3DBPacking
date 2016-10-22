#ifndef CONTAINER_H
#define CONTAINER_H
#include <QString>


class Container
{
public:

    QString type;
    int width; //ширина
    int length; //длина
    int height; //высота

    Container();
    Container(QString t, int w, int l, int h);
    Container(QString t, int w, int h);
    Container(QString t);


};

#endif // CONTAINER_H
