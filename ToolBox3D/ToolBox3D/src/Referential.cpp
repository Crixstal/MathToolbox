#include "Referential.h"

Referential::Referential(const Vector3& center, const Quaternion& quat)
{
    origin = center;
    i = Vector3RotateByQuaternion({ 1.f, 0.f, 0.f }, quat);
    j = Vector3RotateByQuaternion({ 0.f, 1.f, 0.f }, quat);
    k = Vector3RotateByQuaternion({ 0.f, 0.f, 1.f }, quat);
    
    angle = quat.w;
}

void Referential::locToGlobPos(const Referential& local, Vector3& pt)
{
    pt = local.origin + (local.i * pt.x) + (local.j * pt.y) + (local.k * pt.z);
}

void Referential::globToLocPos(const Referential& local, Vector3& pt)
{
    Vector3 OP = pt - local.origin;
    pt.x = dotProduct(OP, local.i);
    pt.y = dotProduct(OP, local.j);
    pt.z = dotProduct(OP, local.k);
}

void Referential::locToGlobVect(const Referential& local, Vector3& vect)
{
    Vector3 OP = (local.i * vect.x) + (local.j * vect.y) + (local.k * vect.z);
    vect = OP;
}

void Referential::globToLocVect(const Referential& local, Vector3& vect)
{
    Vector3 tmpVect = vect;

    vect = {
        dotProduct(tmpVect, local.i),
        dotProduct(tmpVect, local.j),
        dotProduct(tmpVect, local.k)
    };
}