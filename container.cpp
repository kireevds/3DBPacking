#include "container.h"

Container::Container()
{

}

Container::Container(QString t, int w, int l, int h)
{
    type = t;
    width = w;
    length = l;
    height = h;
}

Container::Container(QString t, int w, int h)
{
    type = t;
    width = w;
    length = 0;
    height = h;
}

Container::Container(QString t)
{
    type = t;
    width = 0;
    length = 0;
    height = 0;
}
