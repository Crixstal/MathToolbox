#include "Referential.h"

void Referential::locToGlobPos(const Referential& local, Vector3& pt)
{
    Vector3 locOrigin = { local.origin.x, local.origin.y };
    Vector3 OP = locOrigin + (local.i * pt.x);
    OP += (local.j * pt.y);
    pt.x = OP.x;
    pt.y = OP.y;
}

void Referential::globToLocPos(const Referential& local, Vector3& pt)
{
    Vector3 OP = { pt.x - local.origin.x, pt.y - local.origin.y, pt.z - local.origin.z };
    pt.x = dotProduct(OP, local.i);
    pt.y = dotProduct(OP, local.j);
    pt.z = dotProduct(OP, local.k);
}

void Referential::locToGlobVect(const Referential& local, Vector3& vect)
{
    Vector3 OP = (local.i * vect.x) + (local.j * vect.y) + (local.k * vect.z);
    vect.x = OP.x;
    vect.y = OP.y;
    vect.z = OP.z;
}

void Referential::globToLocVect(const Referential& local, Vector3& vect)
{
    Vector3 tmpVect = vect;

    vect.x = dotProduct(tmpVect, local.i);
    vect.y = dotProduct(tmpVect, local.j);
    vect.z = dotProduct(tmpVect, local.k);
}