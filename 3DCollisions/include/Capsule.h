#pragma once

#include "Maths.h"
#include "Sphere.h"
#include "Cylinder.h"

struct Capsule
{
    Vector3 ptP;
    Vector3 ptQ;
    float radius;

    Capsule(const Vector3& P, const Vector3& Q, const float& r);

    void myDrawCapsule(const Color& color = GREEN);
    bool Segment_Capsule(const Segment& segment, Vector3& interPt, Vector3& interNormal);
    bool Segment_Capsule(const Segment& segment, Vector3& interPt, Vector3& interNormal, bool& isOnCyl);
    void drawIntersection(const Segment& segment, Vector3& interPt, Vector3& interNormal, Color color = GREEN);
};

