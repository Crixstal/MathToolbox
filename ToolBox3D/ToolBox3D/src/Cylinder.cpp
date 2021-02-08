#include "Cylinder.h"

void DrawCircle3D(Vector3 center, float radius, Vector3 rotationAxis, float rotationAngle, Color color)
{
    if (rlCheckBufferLimit(2 * 36)) rlglDraw();

    rlPushMatrix();
    rlTranslatef(center.x, center.y, center.z);
    rlRotatef(rotationAngle, rotationAxis.x, rotationAxis.y, rotationAxis.z);

    rlBegin(RL_LINES);
    for (int i = 0; i < 360; i += 10)
    {
        rlColor4ub(color.r, color.g, color.b, color.a);

        rlVertex3f(sinf(DEG2RAD * i) * radius, cosf(DEG2RAD * i) * radius, 0.0f);
        rlVertex3f(sinf(DEG2RAD * (i + 10)) * radius, cosf(DEG2RAD * (i + 10)) * radius, 0.0f);
    }
    rlEnd();
    rlPopMatrix();
}

void Cylinder::myDrawCylinder(const Vector3& ptA, const Vector3& ptB, const float& radius, Color color)
{
    unsigned int sides = 20.f;

    int numVertex = sides * 6;
    if (rlCheckBufferLimit(numVertex)) rlglDraw();

    rlPushMatrix();
    rlTranslatef(ptA.x, ptA.y, ptA.z);

    float angle = 30;
    rlRotatef(angle, ptB.x, ptB.y, ptB.z);

    rlBegin(RL_TRIANGLES);
    rlColor4ub(color.r, color.g, color.b, color.a);

    // Draw Body -------------------------------------------------------------------------------------
    for (int i = 0; i < 360; i += 360 / sides)
    {
        rlVertex3f(sinf(DEG2RAD * i) * radius, 0, cosf(DEG2RAD * i) * radius); //Bottom Left
        rlVertex3f(sinf(DEG2RAD * (i + 360 / sides)) * radius, 0, cosf(DEG2RAD * (i + 360 / sides)) * radius); //Bottom Right
        rlVertex3f(sinf(DEG2RAD * (i + 360 / sides)) * radius, ptB.y, cosf(DEG2RAD * (i + 360 / sides)) * radius); //Top Right

        rlVertex3f(sinf(DEG2RAD * i) * radius, ptB.y, cosf(DEG2RAD * i) * radius); //Top Left
        rlVertex3f(sinf(DEG2RAD * i) * radius, 0, cosf(DEG2RAD * i) * radius); //Bottom Left
        rlVertex3f(sinf(DEG2RAD * (i + 360 / sides)) * radius, ptB.y, cosf(DEG2RAD * (i + 360 / sides)) * radius); //Top Right
    }

    // Draw Circle A (Base) --------------------------------------------------------------------------------------
    for (int i = 0; i < 360; i += 360 / sides)
    {
        rlVertex3f(ptA.x, ptA.y, ptA.z);
        
        rlVertex3f(sinf(DEG2RAD * (i + 360 / sides)) * radius, ptA.y, cosf(DEG2RAD * (i + 360 / sides)) * radius);
        rlVertex3f(sinf(DEG2RAD * i) * radius, ptA.y, cosf(DEG2RAD * i) * radius);
    }
    
    // Draw Circle B (Top) -----------------------------------------------------------------------------------------
    for (int i = 0; i < 360; i += 360 / sides)
    {
        rlVertex3f(ptB.x, ptB.y, ptB.z);

        rlVertex3f(sinf(DEG2RAD * i) * radius, ptB.y, cosf(DEG2RAD * i) * radius);
        rlVertex3f(sinf(DEG2RAD * (i + 360 / sides)) * radius, ptB.y, cosf(DEG2RAD * (i + 360 / sides)) * radius);
    }
    rlEnd();
    rlPopMatrix();
}

bool Cylinder::Segment_CylinderInfinite(const Segment& segment, const Cylinder& cylinder, Vector3& intersection)
{
    Vector3 P = cylinder.ptA;
    Vector3 Q = cylinder.ptB;
    float radius = cylinder.radius;

    Vector3 AB = vecFromPt(segment.ptA, segment.ptB);
    Vector3 PQ = vecFromPt(P, Q);
    Vector3 PA = vecFromPt(P, segment.ptA);

    float a = dotProduct(PQ, PQ) * dotProduct(AB, AB) - dotProduct(PQ, AB) * dotProduct(PQ, AB);
    if (a == 0)
    {
        std::cout << "a = 0\n" << std::endl;
        return false;
    }

    float c = dotProduct(PQ, PQ) * (dotProduct(PA, PA) - (radius * radius)) - (dotProduct(PA, PQ) * dotProduct(PA, PQ));
    if (c < 0)
    {
        std::cout << "c < 0\n" << std::endl;
        std::cout << "c = " << c << '\n' << std::endl;
        return false;
    }

    float b = dotProduct(PQ, PQ) * dotProduct(PA, AB) - dotProduct(PQ, AB) * dotProduct(PA, PQ);

    float delta = (b * b) - (a * c);
    if (delta < 0)
        return false;

    float root = (-b - sqrt(delta)) / a;
    if (root < 0 || root > 1)
        return false;

    intersection = segment.ptA + root * AB;
    return true;
}

bool Cylinder::Segment_Cylinder(const Segment& segment, const Cylinder& cylinder, Vector3& intersection)
{
    Vector3 P = cylinder.ptA;
    Vector3 Q = cylinder.ptB;
    float radius = cylinder.radius;

    Vector3 AB = vecFromPt(segment.ptA, segment.ptB);
    Vector3 PQ = vecFromPt(P, Q);
    Vector3 PA = vecFromPt(P, segment.ptA);

    //for transform into cylinder non inf
    //Vector3 PM = collisonLineSeg({PQ, P}, seg);

    //if (dotProduct(PM, PQ) < 0 || dotProduct(PM, PQ) > dotProduct(PQ, PQ))
    //    return false;

    float a = dotProduct(PQ, PQ) * dotProduct(AB, AB) - dotProduct(PQ, AB) * dotProduct(PQ, AB);
    if (a == 0)
    {
        std::cout << "a = 0\n" << std::endl;
        return false;
    }

    float c = dotProduct(PQ, PQ) * (dotProduct(PA, PA) - (radius * radius)) - (dotProduct(PA, PQ) * dotProduct(PA, PQ));
    if (c < 0)
    {
        std::cout << "c < 0\n" << std::endl;
        std::cout << "c = " << c << '\n' << std::endl;
        return false;
    }

    float b = dotProduct(PQ, PQ) * dotProduct(PA, AB) - dotProduct(PQ, AB) * dotProduct(PA, PQ);

    float delta = (b * b) - (a * c);
    if (delta < 0)
        return false;

    float root = (-b - sqrt(delta)) / a;
    if (root < 0 || root > 1)
        return false;

    intersection = segment.ptA + root * AB;
    return true;
}