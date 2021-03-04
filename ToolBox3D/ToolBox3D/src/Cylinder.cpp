#include "Cylinder.h"

Cylinder::Cylinder(const Vector3& P, const Vector3& Q, const float& r, const bool& infinite)
{
    ptP = P;
    ptQ = Q;
    radius = r;
    isInfinite = infinite;
}

void Cylinder::myDrawCylinder(const Cylinder& cyl, Color color)
{
    Vector3 PQ = vecFromPt(cyl.ptP, cyl.ptQ);
    float length = vectorMagnitude(PQ);
    Vector3 center = (cyl.ptP + cyl.ptQ) / 2.0f;

    if (isInfinite)
        length += 5.0f;

    rlPushMatrix();
    rlTranslatef(center.x, center.y, center.z);

    Vector3 vect;
    float angle;
    QuaternionToAxisAngle(QuaternionFromVector3ToVector3({ 0.0f, 1.0f, 0.0f }, normalize(PQ)), &vect, &angle);
    rlRotatef(angle * RAD2DEG, vect.x, vect.y, vect.z);
    rlScalef(cyl.radius, length, cyl.radius);

    rlBegin(RL_TRIANGLES);
    rlColor4ub(color.r, color.g, color.b, color.a);

    unsigned int sides = 20;

    for (int i = 0; i < 360; i += 360 / sides)
    {
        Vector3 calcul1 = { sinf(DEG2RAD * i) * cyl.radius, -0.5f, cosf(DEG2RAD * i) * cyl.radius };
        Vector3 calcul2 = { sinf(DEG2RAD * (i + 360 / sides)) * cyl.radius, 0.5f, cosf(DEG2RAD * (i + 360 / sides)) * cyl.radius };
        Vector3 calcul3 = { sinf(DEG2RAD * (i + 360 / sides)) * cyl.radius, -0.5f, cosf(DEG2RAD * (i + 360 / sides))* cyl.radius };
        Vector3 calcul4 = { sinf(DEG2RAD * i) * cyl.radius, 0.5f, cosf(DEG2RAD * i) * cyl.radius };

        rlVertex3f(calcul1.x, calcul1.y, calcul1.z);
        rlVertex3f(calcul3.x, calcul3.y, calcul3.z);
        rlVertex3f(calcul2.x, calcul2.y, calcul2.z);

        rlVertex3f(calcul4.x, calcul4.y, calcul4.z);
        rlVertex3f(calcul1.x, calcul1.y, calcul1.z);
        rlVertex3f(calcul2.x, calcul2.y, calcul2.z);

        if (!isInfinite)
        {
            rlVertex3f(0.0f, -0.5f, 0.0f);
            rlVertex3f(calcul1.x, calcul1.y, calcul1.z);
            rlVertex3f(calcul3.x, calcul3.y, calcul3.z);

            rlVertex3f(0.0f, 0.5f, 0.0f);
            rlVertex3f(calcul4.x, calcul4.y, calcul4.z);
            rlVertex3f(calcul2.x, calcul2.y, calcul2.z);
        }
    }

    rlEnd();
    rlPopMatrix();
}

bool Cylinder::Segment_CylinderInfinite(const Segment& segment, const Cylinder& cyl, Vector3& interPt, Vector3& interNormal)
{
    Vector3 AB = vecFromPt(segment.ptA, segment.ptB);
    Vector3 PQ = vecFromPt(cyl.ptP, cyl.ptQ);
    Vector3 PA = vecFromPt(cyl.ptP, segment.ptA);

    float a = dotProduct(PQ, PQ) * dotProduct(AB, AB) - dotProduct(PQ, AB) * dotProduct(PQ, AB);
    if (a == 0)
        return false;

    float c = dotProduct(PQ, PQ) * (dotProduct(PA, PA) - (cyl.radius * cyl.radius)) - (dotProduct(PA, PQ) * dotProduct(PA, PQ));
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
    Vector3 O, placeholder;
    Plane::Segment_Plane({ cyl.ptP, cyl.ptQ }, interPlane, O, placeholder);
    interNormal = normalize(interPt - O);

    return true;
}

bool Cylinder::Segment_Cylinder(const Segment& segment, const Cylinder& cyl, Vector3& interPt, Vector3& interNormal)
{
    if (!Segment_CylinderInfinite(segment, cyl, interPt, interNormal))
        interPt = segment.ptA;

    Vector3 PQ = vecFromPt(cyl.ptP, cyl.ptQ);
    Vector3 PM = vecFromPt(cyl.ptP, interPt);

    if (dotProduct(PM, PQ) < 0 || dotProduct(PM, PQ) > dotProduct(PQ, PQ))
    {
        Plane Pplane(normalize(-PQ), cyl.ptP);
        Plane Qplane(normalize(PQ), cyl.ptQ);

        float lengthDiff = vectorMagnitude(cyl.ptP - segment.ptA) - vectorMagnitude(cyl.ptQ - segment.ptB);

        if (lengthDiff > 0 && Plane::Segment_Plane(segment, Qplane, interPt, interNormal))
        {
            float len = vectorMagnitude(cyl.ptQ - interPt);

            if (vectorMagnitude(cyl.ptQ - interPt) <= cyl.radius * cyl.radius)
                return true;
        }

        else if (lengthDiff < 0 && Plane::Segment_Plane(segment, Pplane, interPt, interNormal))
            if (vectorMagnitude(cyl.ptP - interPt) <= cyl.radius * cyl.radius)
                return true;
    }

    else
        return true;

    return false;
}

void Cylinder::drawIntersection(const Segment& segment, const Cylinder& cyl, Vector3& interPt, Vector3& interNormal, Color color)
{
    Vector3 normal = normalize(vecFromPt(cyl.ptP, cyl.ptQ));
    Vector3 center = (cyl.ptP + cyl.ptQ) / 2.0f;

    if (isInfinite)
    {
        if (Segment_CylinderInfinite(segment, cyl, interPt, interNormal))
        {
            color = RED;
            DrawSphere(interPt, 0.08f, BROWN);
            DrawLine3D(interPt, interNormal + interPt, PURPLE);
        }
    }

    else
    {
        if (Segment_Cylinder(segment, cyl, interPt, interNormal))
        {
            color = RED;
            DrawSphere(interPt, 0.08f, BROWN);
            DrawLine3D(interPt, interNormal + interPt, PURPLE);
        }
    }

    DrawLine3D(segment.ptA, segment.ptB, color);
    myDrawCylinder(cyl, color);
    DrawLine3D(center, 3 * normal + center, PURPLE);
}