#include "Capsule.h"

#include "Quaternion.h" // already include Mat4 which include Vector3

Capsule::Capsule(const vec3& P, const vec3& Q, const float& r)
{
    ptP = P;
    ptQ = Q;
    radius = r;
}

bool Capsule::Segment_Capsule(const Segment& segment, vec3& interPt, vec3& interNormal)
{
    Cylinder caps(ptP, ptQ, radius, false, quatIdentity());
    if (!caps.Segment_CylinderInfinite(segment, interPt, interNormal))
        interPt = segment.ptA;

    vec3 PQ = vecFromPt(ptP, ptQ);
    vec3 PM = vecFromPt(ptP, interPt);

    if (dotProduct(PM, PQ) < 0 || dotProduct(PM, PQ) > dotProduct(PQ, PQ))
    {
        Sphere caps1(ptP, radius, quatIdentity());
        Sphere caps2(ptQ, radius, quatIdentity());

        if (caps1.Segment_Sphere(segment, interPt, interNormal))
            return true;

        if (caps2.Segment_Sphere(segment, interPt, interNormal))
            return true;
    }

    else
        return true;

    return false;
}

bool Capsule::Segment_Capsule(const Segment& segment, vec3& interPt, vec3& interNormal, bool& isOnCyl)
{
    Cylinder caps(ptP, ptQ, radius, false, quatIdentity());
    if (!caps.Segment_CylinderInfinite(segment, interPt, interNormal))
        interPt = segment.ptA;

    vec3 PQ = vecFromPt(ptP, ptQ);
    vec3 PM = vecFromPt(ptP, interPt);

    if (dotProduct(PM, PQ) < 0 || dotProduct(PM, PQ) > dotProduct(PQ, PQ))
    {
        Sphere caps1(ptP, radius, quatIdentity());
        Sphere caps2(ptQ, radius, quatIdentity());

        if (caps1.Segment_Sphere(segment, interPt, interNormal))
            return true;

        if (caps2.Segment_Sphere(segment, interPt, interNormal))
            return true;
    }

    else
    {
        isOnCyl = true;
        return true;
    }

    return false;
}