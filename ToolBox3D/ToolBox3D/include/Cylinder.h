#pragma once

#include <raylib.h>

struct Cylinder
{
    Vector3 pointA;
    Vector3 pointB;
    float radius;
    bool infinite = false;

    void myDrawCylinder(Vector3 position, float radiusTop, float radiusBottom, float height, int sides, Color color = LIGHTGRAY);
    bool Segment_CylinderInfinite(const Vector3& vecA, const Vector3& vecB, Cylinder cylinder, Vector3& interPt, Vector3& interNormal);
};

