#include "Quad.h"

void Quad::myDrawRectangle(Vector3 center, Vector3 unitNormal, Vector2 extensions, Color rectColor)
{
    if (Vector3LengthSqr(unitNormal) < 1e-4) return;
    unitNormal = Vector3Normalize(unitNormal);

    int numVertex = 6;
    if (rlCheckBufferLimit(numVertex)) rlglDraw();

    rlPushMatrix();
    rlTranslatef(center.x, center.y, center.z);

    Vector3 vect;
    float angle;
    QuaternionToAxisAngle(QuaternionFromVector3ToVector3({ 0,1,0 }, unitNormal), &vect, &angle);
    rlRotatef(angle * RAD2DEG, vect.x, vect.y, vect.z);

    rlScalef(extensions.x, 1, extensions.y);

    rlBegin(RL_TRIANGLES);
    rlColor4ub(rectColor.r, rectColor.g, rectColor.b, rectColor.a);

    rlVertex3f(-1, 0, -1);
    rlVertex3f(-1, 0, 1);
    rlVertex3f(1, 0, 1);

    rlVertex3f(-1, 0, -1);
    rlVertex3f(1, 0, 1);
    rlVertex3f(1, 0, -1);

    rlEnd();
    rlPopMatrix();
}