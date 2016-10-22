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

bool SortingAlg::maxToLowXZY(const Object *lhs, const Object *rhs)
{
    if (lhs->width != rhs->width)
        return lhs->width > rhs->width;
    if (lhs->height!= rhs->height)
        return lhs->height > rhs->height;
    return lhs->length > rhs->length;
}

bool SortingAlg::maxToLowYXZ(const Object *lhs, const Object *rhs)
{
    if (lhs->length != rhs->length)
        return lhs->length > rhs->length;
    if (lhs->width!= rhs->width)
        return lhs->width > rhs->width;
    return lhs->height > rhs->height;
}

bool SortingAlg::maxToLowYZX(const Object *lhs, const Object *rhs)
{
    if (lhs->length != rhs->length)
        return lhs->length > rhs->length;
    if (lhs->height!= rhs->height)
        return lhs->height > rhs->height;
    return lhs->width > rhs->width;
}

bool SortingAlg::maxToLowZXY(const Object *lhs, const Object *rhs)
{
    if (lhs->height != rhs->height)
        return lhs->height > rhs->height;
    if (lhs->width!= rhs->width)
        return lhs->width > rhs->width;
    return lhs->length > rhs->length;
}

bool SortingAlg::maxToLowZYX(const Object *lhs, const Object *rhs)
{
    if (lhs->height != rhs->height)
        return lhs->height > rhs->height;
    if (lhs->length!= rhs->length)
        return lhs->length > rhs->length;
    return lhs->height > rhs->height;
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
