#pragma once

#include <iostream>

#include "Maths.h"
#include "Plane.h"

struct Cylinder
{
    Vector3 ptP;
    Vector3 ptQ;
    float radius;
    bool isInfinite;

    Cylinder(const Vector3& P, const Vector3& Q, const float& r, const bool& infinite);

    void myDrawCylinder(Color color = GREEN);
    bool Segment_CylinderInfinite(const Segment& segment, Vector3& interPt, Vector3& interNormal);
    bool Segment_Cylinder(const Segment& segment, Vector3& interPt, Vector3& interNormal);
    void drawIntersection(const Segment& segment, Vector3& interPt, Vector3& interNormal, Color color = GREEN);
};