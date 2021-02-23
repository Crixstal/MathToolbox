#include "Quad.h"

void Quad::myDrawQuad(const Vector3& center, const Vector3& size, const Quaternion& quaternion, Color color)
{
    if (Vector3LengthSqr(unitNormal) < 1e-4)
        return;

    unitNormal = Vector3Normalize(unitNormal);

    int numVertex = 6;
    if (rlCheckBufferLimit(numVertex))
        rlglDraw();

    rlPushMatrix();
    rlTranslatef(center.x, center.y, center.z);

    Vector3 vect;
    float angle;
    QuaternionToAxisAngle(quaternion, &vect, &angle);
    rlRotatef(angle * RAD2DEG, vect.x, vect.y, vect.z);

    rlScalef(size.x, 1, size.y);

    rlBegin(RL_TRIANGLES);
    rlColor4ub(color.r, color.g, color.b, color.a);

    rlVertex3f(-1, 0, -1);
    rlVertex3f(-1, 0, 1);
    rlVertex3f(1, 0, 1);

    rlVertex3f(-1, 0, -1);
    rlVertex3f(1, 0, 1);
    rlVertex3f(1, 0, -1);

    rlEnd();
    rlPopMatrix();
}

/*
bool Quad::Segment_Quad(const Segment& segment, const Quad& quad, Vector3& interPt, Vector3& interNormal)
{

}*/