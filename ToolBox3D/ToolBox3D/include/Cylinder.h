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
    Quaternion quaternion;

    Cylinder(const Vector3& P, const Vector3& Q, const float& r, const bool& infinite, const Quaternion& q);

    void myDrawCylinder(const Color& color = GREEN, const int& resLat = 20, const float& startLat = 0, const float& endLat = 2 * PI);
    bool Segment_CylinderInfinite(const Segment& segment, Vector3& interPt, Vector3& interNormal);
    bool Segment_Cylinder(const Segment& segment, Vector3& interPt, Vector3& interNormal);
    void drawIntersection(const Segment& segment, Vector3& interPt, Vector3& interNormal, Color color = GREEN);
};