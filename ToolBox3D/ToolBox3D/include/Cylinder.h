#pragma once

#include <raylib.h>

struct Cylinder
{
    Vector3 pointA;
    Vector3 pointB;
    float radius;
    bool infinite = false;

    bool Segment_Cylinder();
};

