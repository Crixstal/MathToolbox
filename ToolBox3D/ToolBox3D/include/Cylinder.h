#pragma once

#include <raylib.h>
#include <rlgl.h>

struct Cylinder
{
    Vector3 ptA;
    Vector3 ptB;
    float radius;
    bool infinite = false;

    void myDrawCylinder(const Vector3& ptA, const Vector3& ptB, const float& radius, Color color = GREEN);

    bool Segment_CylinderInfinite(const Vector3& vecA, const Vector3& vecB, Cylinder cylinder, Vector3& interPt, Vector3& interNormal);
};

