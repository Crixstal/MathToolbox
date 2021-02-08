#pragma once

#include <iostream>

#include "Maths.h"

struct Cylinder
{
    Vector3 ptA;
    Vector3 ptB;
    float radius;
    bool infinite = false;

    void myDrawCylinder(const Vector3& ptA, const Vector3& ptB, const float& radius, Color color = GREEN);

    bool Segment_CylinderInfinite(const Segment& segment, const Cylinder& cylinder, Vector3& intersection);

    bool Segment_Cylinder(const Segment& segment, const Cylinder& cylinder, Vector3& intersection);
};

