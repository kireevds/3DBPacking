#ifndef SORTINGALG_H
#define SORTINGALG_H
#include <object.h>


class SortingAlg
{
public:
    SortingAlg();

    bool static lowToMaxV(const Object *lhs, const Object *rhs); //static даёт возможность вызвать ф-ю без объекта. По идее, потом надо переделать в lib
    bool static maxToLowV(const Object *lhs, const Object *rhs);
    bool static maxToLowXYZ(const Object *lhs, const Object *rhs);
    bool static maxToLowXZY(const Object *lhs, const Object *rhs);
    bool static maxToLowYXZ(const Object *lhs, const Object *rhs);
    bool static maxToLowYZX(const Object *lhs, const Object *rhs);
    bool static maxToLowZXY(const Object *lhs, const Object *rhs);
    bool static maxToLowZYX(const Object *lhs, const Object *rhs);
    bool static maxW1W2minW3(const Object *lhs, const Object *rhs);
    bool static minW1W2maxW3(const Object *lhs, const Object *rhs);

    bool static maxToLowCXYZ(const Object *lhs, const Object *rhs); //по координатам
    bool static maxToLowCXZY(const Object *lhs, const Object *rhs);
    bool static maxToLowCYXZ(const Object *lhs, const Object *rhs);
    bool static maxToLowCYZX(const Object *lhs, const Object *rhs);
    bool static maxToLowCZXY(const Object *lhs, const Object *rhs);
    bool static maxToLowCZYX(const Object *lhs, const Object *rhs);

    bool static minPw_w(const Object *lhs, const Object *rhs);
    bool static maxPw_w(const Object *lhs, const Object *rhs);
};

#endif // SORTINGALG_H
