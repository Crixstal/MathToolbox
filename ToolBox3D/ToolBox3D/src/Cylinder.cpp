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