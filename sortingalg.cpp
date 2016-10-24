#include "sortingalg.h"

SortingAlg::SortingAlg()
{}

bool SortingAlg::lowToMaxV(const Object* lhs, const Object* rhs)
{
    return lhs->result < rhs->result;
}

bool SortingAlg::maxToLowV(const Object* lhs, const Object* rhs)
{
    return lhs->result > rhs->result;
}

bool SortingAlg::maxToLowXYZ(const Object* lhs, const Object* rhs)
{
    if (lhs->width != rhs->width)
        return lhs->width > rhs->width;
    if (lhs->length!= rhs->length)
        return lhs->length > rhs->length;
    return lhs->height > rhs->height;
}

bool SortingAlg::maxToLowCXYZ(const Object* lhs, const Object* rhs)
{
    if (lhs->x != rhs->x)
        return lhs->x > rhs->x;
    if (lhs->y!= rhs->y)
        return lhs->y > rhs->y;
    return lhs->z > rhs->z;
}

bool SortingAlg::maxToLowXZY(const Object *lhs, const Object *rhs)
{
    if (lhs->width != rhs->width)
        return lhs->width > rhs->width;
    if (lhs->height!= rhs->height)
        return lhs->height > rhs->height;
    return lhs->length > rhs->length;
}

bool SortingAlg::maxToLowCXZY(const Object *lhs, const Object *rhs)
{
    if (lhs->x != rhs->x)
        return lhs->x > rhs->x;
    if (lhs->z!= rhs->z)
        return lhs->z > rhs->z;
    return lhs->y > rhs->y;
}

bool SortingAlg::maxToLowYXZ(const Object *lhs, const Object *rhs)
{
    if (lhs->length != rhs->length)
        return lhs->length > rhs->length;
    if (lhs->width!= rhs->width)
        return lhs->width > rhs->width;
    return lhs->height > rhs->height;
}

bool SortingAlg::maxToLowCYXZ(const Object *lhs, const Object *rhs)
{
    if (lhs->y != rhs->y)
        return lhs->y > rhs->y;
    if (lhs->x!= rhs->x)
        return lhs->x > rhs->x;
    return lhs->z > rhs->z;
}

bool SortingAlg::maxToLowYZX(const Object *lhs, const Object *rhs)
{
    if (lhs->length != rhs->length)
        return lhs->length > rhs->length;
    if (lhs->height!= rhs->height)
        return lhs->height > rhs->height;
    return lhs->width > rhs->width;
}

bool SortingAlg::maxToLowCYZX(const Object *lhs, const Object *rhs)
{
    if (lhs->y != rhs->y)
        return lhs->y > rhs->y;
    if (lhs->z!= rhs->z)
        return lhs->z > rhs->z;
    return lhs->x > rhs->x;
}

bool SortingAlg::maxToLowZXY(const Object *lhs, const Object *rhs)
{
    if (lhs->height != rhs->height)
        return lhs->height > rhs->height;
    if (lhs->width!= rhs->width)
        return lhs->width > rhs->width;
    return lhs->length > rhs->length;
}

bool SortingAlg::maxToLowCZXY(const Object *lhs, const Object *rhs)
{
    if (lhs->z != rhs->z)
        return lhs->z > rhs->z;
    if (lhs->x!= rhs->x)
        return lhs->x > rhs->x;
    return lhs->y > rhs->y;
}

bool SortingAlg::maxToLowZYX(const Object *lhs, const Object *rhs)
{
    if (lhs->height != rhs->height)
        return lhs->height > rhs->height;
    if (lhs->length!= rhs->length)
        return lhs->length > rhs->length;
    return lhs->width > rhs->width;
}

bool SortingAlg::maxToLowCZYX(const Object *lhs, const Object *rhs)
{
    if (lhs->z != rhs->z)
        return lhs->z > rhs->z;
    if (lhs->y!= rhs->y)
        return lhs->y > rhs->y;
    return lhs->x > rhs->x;
}

bool SortingAlg::maxW1W2minW3(const Object *lhs, const Object *rhs)
{
    if (lhs->result != rhs->result)
        return lhs->result > rhs->result;
    return lhs->height < rhs->height;
}

bool SortingAlg::minW1W2maxW3(const Object *lhs, const Object *rhs)
{
    if (lhs->result != rhs->result)
        return lhs->result < rhs->result;
    return lhs->height > rhs->height;
}

bool SortingAlg::maxPw_w(const Object *lhs, const Object *rhs)
{
    if ((lhs->height - lhs->wz.toInt()) != (rhs->height - rhs->wz.toInt()))
        return (lhs->height - lhs->wz.toInt()) > (rhs->height - rhs->wz.toInt());
    if ((lhs->length - lhs->wy.toInt()) != (rhs->length - rhs->wy.toInt()))
        return (lhs->length - lhs->wy.toInt()) > (rhs->length - rhs->wy.toInt());
    return (lhs->width - lhs->wx.toInt()) > (rhs->width - rhs->wx.toInt());
}

bool SortingAlg::minPw_w(const Object *lhs, const Object *rhs)
{
    if ((lhs->width - lhs->wx.toInt()) != (rhs->width - rhs->wx.toInt()))
        return (lhs->width - lhs->wx.toInt()) < (rhs->width - rhs->wx.toInt());
    if ((lhs->length - lhs->wy.toInt()) != (rhs->length - rhs->wy.toInt()))
        return (lhs->length - lhs->wy.toInt()) < (rhs->length - rhs->wy.toInt());
    return (lhs->height - lhs->wz.toInt()) < (rhs->height - rhs->wz.toInt());
}
