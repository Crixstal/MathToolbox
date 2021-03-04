#include "Capsule.h"

Capsule::Capsule(const Vector3& P, const Vector3& Q, const float& r)
{
    ptP = P;
    ptQ = Q;
    radius = r;
}

void Capsule::myDrawCapsule(const Capsule& caps, Color color)
{
    Vector3 PQ = vecFromPt(caps.ptP, caps.ptQ);
    float length = vectorMagnitude(PQ);
    Vector3 center = (caps.ptP + caps.ptQ) / 2.0f;

    rlPushMatrix();
    rlTranslatef(center.x, center.y, center.z);

    Vector3 vect;
    float angle;
    QuaternionToAxisAngle(QuaternionFromVector3ToVector3({ 0.0f, 1.0f, 0.0f }, normalize(PQ)), &vect, &angle);
    rlRotatef(angle * RAD2DEG, vect.x, vect.y, vect.z);
    rlScalef(caps.radius, length, caps.radius);

    rlBegin(RL_TRIANGLES);
    rlColor4ub(color.r, color.g, color.b, color.a);

    unsigned int sides = 20;

    for (int i = 0; i < 360; i += 360 / sides)
    {
        Vector3 calcul1 = { sinf(DEG2RAD * i) * caps.radius, -0.5f, cosf(DEG2RAD * i) * caps.radius };
        Vector3 calcul2 = { sinf(DEG2RAD * (i + 360 / sides)) * caps.radius, 0.5f, cosf(DEG2RAD * (i + 360 / sides)) * caps.radius };
        Vector3 calcul3 = { sinf(DEG2RAD * (i + 360 / sides)) * caps.radius, -0.5f, cosf(DEG2RAD * (i + 360 / sides)) * caps.radius };
        Vector3 calcul4 = { sinf(DEG2RAD * i) * caps.radius, 0.5f, cosf(DEG2RAD * i) * caps.radius };

        rlVertex3f(calcul1.x, calcul1.y, calcul1.z);
        rlVertex3f(calcul3.x, calcul3.y, calcul3.z);
        rlVertex3f(calcul2.x, calcul2.y, calcul2.z);

        rlVertex3f(calcul4.x, calcul4.y, calcul4.z);
        rlVertex3f(calcul1.x, calcul1.y, calcul1.z);
        rlVertex3f(calcul2.x, calcul2.y, calcul2.z);

        //Sphere::myDrawSphere(20, 20, 0, 0, PI, PI, color);
        //Sphere::myDrawSphere(20, 20, 0, PI, 0, PI, color);
    }

    rlEnd();
    rlPopMatrix();
}
/*
bool Capsule::Segment_Capsule(const Segment& segment, const Capsule& caps, Vector3& interPt, Vector3& interNormal)
{
    if (!Cylinder::Segment_CylinderInfinite(segment, caps, interPt, interNormal))
        interPt = segment.ptA;

    Vector3 PQ = vecFromPt(caps.ptP, caps.ptQ);
    Vector3 PM = vecFromPt(caps.ptP, interPt);

    if (dotProduct(PM, PQ) < 0 || dotProduct(PM, PQ) > dotProduct(PQ, PQ))
    {
        Plane Pplane(normalize(-PQ), caps.ptP);
        Plane Qplane(normalize(PQ), caps.ptQ);

        float lengthDiff = vectorMagnitude(caps.ptP - segment.ptA) - vectorMagnitude(caps.ptQ - segment.ptB);

        if (lengthDiff > 0 && Plane::Segment_Plane(segment, Qplane, interPt, interNormal))
        {
            float len = vectorMagnitude(caps.ptQ - interPt);

            if (vectorMagnitude(caps.ptQ - interPt) <= caps.radius * caps.radius)
                return true;
        }

        else if (lengthDiff < 0 && Plane::Segment_Plane(segment, Pplane, interPt, interNormal))
            if (vectorMagnitude(caps.ptP - interPt) <= caps.radius * caps.radius)
                return true;
    }

    else
        return true;

    return false;
}

void Capsule::drawIntersection(const Segment& segment, const Capsule& caps, Vector3& interPt, Vector3& interNormal, Color color)
{
    Vector3 normal = normalize(vecFromPt(caps.ptP, caps.ptQ));
    Vector3 center = (caps.ptP + caps.ptQ) / 2.0f;

    if (isInfinite)
    {
        if (Segment_CapsuleInfinite(segment, caps, interPt, interNormal))
        {
            color = RED;
            DrawSphere(interPt, 0.08f, BROWN);
            DrawLine3D(interPt, interNormal + interPt, PURPLE);
        }
    }

    else
    {
        if (Segment_Capsule(segment, caps, interPt, interNormal))
        {
            color = RED;
            DrawSphere(interPt, 0.08f, BROWN);
            DrawLine3D(interPt, interNormal + interPt, PURPLE);
        }
    }

    DrawLine3D(segment.ptA, segment.ptB, color);
    myDrawCapsule(caps, color);
    DrawLine3D(center, 3 * normal + center, PURPLE);
}*/