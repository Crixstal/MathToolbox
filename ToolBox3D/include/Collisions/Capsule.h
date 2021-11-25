#pragma once

#include "Definitions.h"
#include "Sphere.h"
#include "Cylinder.h"

struct Capsule
{
    vec3 ptP;
    vec3 ptQ;
    float radius;

    Capsule(const vec3& P, const vec3& Q, const float& r);

    bool Segment_Capsule(const Segment& segment, vec3& interPt, vec3& interNormal);
    bool Segment_Capsule(const Segment& segment, vec3& interPt, vec3& interNormal, bool& isOnCyl);
};

