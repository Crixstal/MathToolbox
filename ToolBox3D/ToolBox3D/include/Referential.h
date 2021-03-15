#pragma once

#include "Maths.h"

struct Referential
{
    Vector3 origin;
    Vector3 i;
    Vector3 j;
    Vector3 k;
    float angle;

    void locToGlobPos(const Referential& local, Vector3& pt);
    void globToLocPos(const Referential& local, Vector3& pt);

    void locToGlobVect(const Referential& local, Vector3& vect);
    void globToLocVect(const Referential& local, Vector3& vect);
};