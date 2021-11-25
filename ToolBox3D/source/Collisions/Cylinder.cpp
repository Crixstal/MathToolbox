#include "Cylinder.h"

#include "Vector3.h"

Cylinder::Cylinder(const vec3& P, const vec3& Q, const float& r, const bool& infinite, const quat& q)
{
    ptP = P;
    ptQ = Q;
    radius = r;
    isInfinite = infinite;
    quaternion = q;
}

bool Cylinder::Segment_CylinderInfinite(const Segment& segment, vec3& interPt, vec3& interNormal)
{
    vec3 AB = vecFromPt(segment.ptA, segment.ptB);
    vec3 PQ = vecFromPt(ptP, ptQ);
    vec3 PA = vecFromPt(ptP, segment.ptA);

    float a = dotProduct(PQ, PQ) * dotProduct(AB, AB) - dotProduct(PQ, AB) * dotProduct(PQ, AB);
    if (a == 0)
        return false;

    float c = dotProduct(PQ, PQ) * (dotProduct(PA, PA) - (radius * radius)) - (dotProduct(PA, PQ) * dotProduct(PA, PQ));
    if (c < 0)
        return false;

    float b = dotProduct(PQ, PQ) * dotProduct(PA, AB) - dotProduct(PQ, AB) * dotProduct(PA, PQ);

    float delta = (b * b) - (a * c);
    if (delta < 0)
        return false;

    float root = (-b - sqrt(delta)) / a;
    if (root < 0 || root > 1)
        return false;

    interPt = segment.ptA + root * AB;

    Plane interPlane(normalize(PQ), interPt);
    vec3 otherInterPt, otherInterNormal;
    interPlane.Segment_Plane({ ptP, ptQ }, otherInterPt, otherInterNormal);
    interNormal = normalize(interPt - otherInterPt);

    return true;
}

bool Cylinder::Segment_Cylinder(const Segment& segment, vec3& interPt, vec3& interNormal)
{
    if (!Segment_CylinderInfinite(segment, interPt, interNormal))
        interPt = segment.ptA;

    vec3 PQ = vecFromPt(ptP, ptQ);
    vec3 PM = vecFromPt(ptP, interPt);

    if (dotProduct(PM, PQ) < 0 || dotProduct(PM, PQ) > dotProduct(PQ, PQ))
    {
        Plane Pplane(normalize(-PQ), ptP);
        Plane Qplane(normalize(PQ), ptQ);

        float lengthDiff = vecMagnitude(ptP - segment.ptA) - vecMagnitude(ptQ - segment.ptB);

        if (lengthDiff > 0 && Qplane.Segment_Plane(segment, interPt, interNormal))
        {
            float len = vecMagnitude(ptQ - interPt);

            if (vecMagnitude(ptQ - interPt) <= radius * radius)
                return true;
        }

        else if (lengthDiff < 0 && Pplane.Segment_Plane(segment, interPt, interNormal))
            if (vecMagnitude(ptP - interPt) <= radius * radius)
                return true;
    }

    else
        return true;

    return false;
}