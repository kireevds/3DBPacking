#ifndef OBJECT_H
#define OBJECT_H
#include <QString>


class Object
{
public:
    QString type;

    int width; //ширина X
    int length; //длина Y
    int height; //высота Z

    int x; //координаты точки, ближайшей к началу координат
    int y;
    int z;

    int result; //переменная для сортировки

    Object();
    Object(QString t, int w, int l, int h, int r);
};

#endif // OBJECT_H
