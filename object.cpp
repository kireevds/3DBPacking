#include "object.h"

Object::Object()
{

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
}
