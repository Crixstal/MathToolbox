#include "geometric_prim.h"

void locToGlobPos(referential2 local, point2* pt)
{
    vector2 locOrigin = {local.origin.x, local.origin.y};
    vector2 OP = addition(locOrigin, scale(local.i, pt->x));
    OP = addition(OP, scale(local.j, pt->y));
    pt->x = OP.x;
    pt->y = OP.y;
}

void globToLocPos(referential2 local, point2* pt)
{
    vector2 OP = {pt->x - local.origin.x, pt->y - local.origin.y};
    pt->x = dotProduct(OP, local.i);
    pt->y = dotProduct(OP, local.j);
}

void locToGlobVect(referential2 local, vector2* vect)
{
    vector2 OP = addition(scale(local.i, vect->x), scale(local.j, vect->y));
    vect->x = OP.x;
    vect->y = OP.y;
}

void globToLocVect(referential2 local, vector2* vect)
{
    vector2 tmpVect = *vect;

    vect->x = dotProduct(tmpVect, local.i);
    vect->y = dotProduct(tmpVect, local.j);
}
