#include "object.h"

Object::Object()
{
    result = -5;
    flag = false;
}

Object::Object(const Object &obj)
{
    type = obj.type;
    width = obj.width;
    length = obj.length;
    height = obj.height;
    x = obj.x;
    y = obj.y;
    z = obj.z;
    result = obj.result;
    flag = false;
}

Object::Object(QString t, int w, int l, int h, int r)
{
    type = t;
    width = w;
    length = l;
    height = h;
    x = -1;
    y = -1;
    z = -1;
    result = r;
    flag = false;
}
