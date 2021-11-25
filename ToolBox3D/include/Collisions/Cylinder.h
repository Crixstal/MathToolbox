#pragma once

#include <iostream>

#include "Definitions.h"
#include "Plane.h"

struct Cylinder
{
    vec3 ptP;
    vec3 ptQ;
    float radius;
    bool isInfinite;
    quat quaternion;

    Cylinder(const vec3& P, const vec3& Q, const float& r, const bool& infinite, const quat& q);

    bool Segment_CylinderInfinite(const Segment& segment, vec3& interPt, vec3& interNormal);
    bool Segment_Cylinder(const Segment& segment, vec3& interPt, vec3& interNormal);
};