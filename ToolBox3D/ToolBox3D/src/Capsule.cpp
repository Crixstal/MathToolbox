#include "Capsule.h"

Capsule::Capsule(const Vector3& P, const Vector3& Q, const float& r)
{
    ptP = P;
    ptQ = Q;
    radius = r;
}

void Capsule::myDrawCapsule(const Color& color)
{
    Cylinder caps(ptP, ptQ, radius, true);
    caps.myDrawCylinder(color, 20, 0, 2 * PI);

    Sphere sphere1(ptP, radius);
    Sphere sphere2(ptQ, radius);
    sphere1.myDrawSphere(20, 20, 0, 0, 2 * PI, PI, color);
    sphere2.myDrawSphere(20, 20, 0, 0, 2 * PI, PI, color);
}

bool Capsule::Segment_Capsule(const Segment& segment, Vector3& interPt, Vector3& interNormal)
{
    Cylinder caps(ptP, ptQ, radius, false);
    if (!caps.Segment_CylinderInfinite(segment, interPt, interNormal))
        interPt = segment.ptA;

    Vector3 PQ = vecFromPt(ptP, ptQ);
    Vector3 PM = vecFromPt(ptP, interPt);

    if (dotProduct(PM, PQ) < 0 || dotProduct(PM, PQ) > dotProduct(PQ, PQ))
    {
        Sphere caps1(ptP, radius);
        Sphere caps2(ptQ, radius);

        if (caps1.Segment_Sphere(segment, interPt, interNormal))
            return true;

        if (caps2.Segment_Sphere(segment, interPt, interNormal))
                return true;
    }

    else
        return true;

    return false;
}

void Capsule::drawIntersection(const Segment& segment, Vector3& interPt, Vector3& interNormal, Color color)
{
    Vector3 normal = normalize(vecFromPt(ptP, ptQ));
    Vector3 center = (ptP + ptQ) / 2.0f;

    if (Segment_Capsule(segment, interPt, interNormal))
    {
        color = RED;
        DrawSphere(interPt, 0.08f, BROWN);
        DrawLine3D(interPt, interNormal + interPt, PURPLE);
    }

    DrawLine3D(segment.ptA, segment.ptB, color);
    myDrawCapsule(color);
    DrawLine3D(center, 3 * normal + center, PURPLE);
}