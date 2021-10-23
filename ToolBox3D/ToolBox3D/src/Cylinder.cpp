#include "Cylinder.h"

Cylinder::Cylinder(const Vector3& P, const Vector3& Q, const float& r, const bool& infinite, const Quaternion& q)
{
    ptP = P;
    ptQ = Q;
    radius = r;
    isInfinite = infinite;
    quaternion = q;
}

void Cylinder::myDrawCylinder(const Color& color, const int& resLat, const float& startLat, const float& endLat)
{
    float stepLat = (endLat - startLat) / (float)resLat;

    Vector3 PQ = vecFromPt(ptP, ptQ);
    float length = vectorMagnitude(PQ);
    Vector3 center = (ptP + ptQ) / 2.0f;

    rlPushMatrix();
    rlTranslatef(center.x, center.y, center.z);

    Vector3 vect;
    float angle;
    QuaternionToAxisAngle(QuaternionFromVector3ToVector3({ 0.0f, 1.0f, 0.0f }, normalize(PQ)), &vect, &angle);
    rlRotatef(angle * RAD2DEG, vect.x, vect.y, vect.z);

    rlScalef(radius, length, radius);

    rlBegin(RL_TRIANGLES);
    rlColor4ub(color.r, color.g, color.b, color.a);

    for (int i = 0; i < resLat; ++i)
    {
        float theta0 = i * stepLat + startLat;
        float theta1 = (i + 1 == resLat) ? endLat : (i + 1) * stepLat + startLat;

        Vector3 calcul1 = { sinf(theta0), -0.5f, cosf(theta0) };
        Vector3 calcul2 = { sinf(theta0), 0.5f, cosf(theta0) };
        Vector3 calcul3 = { sinf(theta1), -0.5f, cosf(theta1) };
        Vector3 calcul4 = { sinf(theta1), 0.5f, cosf(theta1) };

        rlVertex3f(calcul1.x, calcul1.y, calcul1.z);
        rlVertex3f(calcul3.x, calcul3.y, calcul3.z);
        rlVertex3f(calcul2.x, calcul2.y, calcul2.z);

        rlVertex3f(calcul3.x, calcul3.y, calcul3.z);
        rlVertex3f(calcul4.x, calcul4.y, calcul4.z);
        rlVertex3f(calcul2.x, calcul2.y, calcul2.z);

        if (!isInfinite)
        {
            rlVertex3f(0.0f, -0.5f, 0.0f);
            rlVertex3f(calcul3.x, calcul3.y, calcul3.z);
            rlVertex3f(calcul1.x, calcul1.y, calcul1.z);

            rlVertex3f(0.0f, 0.5f, 0.0f);
            rlVertex3f(calcul2.x, calcul2.y, calcul2.z);
            rlVertex3f(calcul4.x, calcul4.y, calcul4.z);
        }
    }

    rlEnd();
    rlPopMatrix();
}

bool Cylinder::Segment_CylinderInfinite(const Segment& segment, Vector3& interPt, Vector3& interNormal)
{
    Vector3 AB = vecFromPt(segment.ptA, segment.ptB);
    Vector3 PQ = vecFromPt(ptP, ptQ);
    Vector3 PA = vecFromPt(ptP, segment.ptA);

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
    Vector3 otherInterPt, otherInterNormal;
    interPlane.Segment_Plane({ ptP, ptQ }, otherInterPt, otherInterNormal);
    interNormal = normalize(interPt - otherInterPt);

    return true;
}

bool Cylinder::Segment_Cylinder(const Segment& segment, Vector3& interPt, Vector3& interNormal)
{
    if (!Segment_CylinderInfinite(segment, interPt, interNormal))
        interPt = segment.ptA;

    Vector3 PQ = vecFromPt(ptP, ptQ);
    Vector3 PM = vecFromPt(ptP, interPt);

    if (dotProduct(PM, PQ) < 0 || dotProduct(PM, PQ) > dotProduct(PQ, PQ))
    {
        Plane Pplane(normalize(-PQ), ptP);
        Plane Qplane(normalize(PQ), ptQ);

        float lengthDiff = vectorMagnitude(ptP - segment.ptA) - vectorMagnitude(ptQ - segment.ptB);

        if (lengthDiff > 0 && Qplane.Segment_Plane(segment, interPt, interNormal))
        {
            float len = vectorMagnitude(ptQ - interPt);

            if (vectorMagnitude(ptQ - interPt) <= radius * radius)
                return true;
        }

        else if (lengthDiff < 0 && Pplane.Segment_Plane(segment, interPt, interNormal))
            if (vectorMagnitude(ptP - interPt) <= radius * radius)
                return true;
    }

    else
        return true;

    return false;
}

void Cylinder::drawIntersection(const Segment& segment, Vector3& interPt, Vector3& interNormal, Color color)
{
    Vector3 normal = normalize(vecFromPt(ptP, ptQ));
    Vector3 center = (ptP + ptQ) / 2.0f;

    if (isInfinite)
    {
        if (Segment_CylinderInfinite(segment, interPt, interNormal))
        {
            color = RED;
            DrawSphere(interPt, 0.08f, BROWN);
            DrawLine3D(interPt, interNormal + interPt, PURPLE);
        }
    }

    else
    {
        if (Segment_Cylinder(segment, interPt, interNormal))
        {
            color = RED;
            DrawSphere(interPt, 0.08f, BROWN);
            DrawLine3D(interPt, interNormal + interPt, PURPLE);
        }
    }

    DrawLine3D(segment.ptA, segment.ptB, color);
    myDrawCylinder(color);
    DrawLine3D(center, 3 * normal + center, PURPLE);
}