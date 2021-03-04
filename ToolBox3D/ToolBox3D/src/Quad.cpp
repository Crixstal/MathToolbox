#include "Quad.h"
#include "Plane.h"

Quad::Quad(const Vector3& c, const Quaternion& q, const Vector2& e)
{
    center = c;
    quaternion = q;
    extension = e;
}

void Quad::myDrawQuad(const Quad& quad, Color color)
{
    rlPushMatrix();
    rlTranslatef(quad.center.x, quad.center.y, quad.center.z);

    Vector3 vect;
    float angle;
    QuaternionToAxisAngle(quad.quaternion, &vect, &angle);
    rlRotatef(angle * RAD2DEG, vect.x, vect.y, vect.z);

    rlScalef(quad.extension.x, 1.0f, quad.extension.y);

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

bool Quad::Segment_Quad(const Segment& segment, const Quad& quad, Vector3& interPt, Vector3& interNormal)
{
    Vector3 normal = normalize(Vector3RotateByQuaternion({ 0.0f, 1.0f, 0.0f }, quad.quaternion));

    Plane plane (normal, quad.center);

    if (!Plane::Segment_Plane(segment, plane, interPt, interNormal))
        return false;

    Vector3 i = Vector3RotateByQuaternion({0.0f, 1.0f, 0.0f}, quad.quaternion);
    Vector3 j = Vector3RotateByQuaternion({1.0f, 0.0f, 1.0f}, quad.quaternion);
    Vector3 vect = interPt - quad.center;

    if (fabsf(dotProduct(i, vect)) > quad.extension.x ||
        fabsf(dotProduct(j, vect)) > quad.extension.y)
        return false;

    return true;
}

void Quad::drawIntersection(const Segment& segment, const Quad& quad, Vector3& interPt, Vector3& interNormal, Color color)
{
    Vector3 normal = Vector3RotateByQuaternion({ 0.0f, 1.0f, 0.0f }, quad.quaternion);

    if (Segment_Quad(segment, quad, interPt, interNormal))
    {
        color = RED;
        DrawSphere(interPt, 0.08f, BROWN);
        DrawLine3D(interPt, interNormal + interPt, PURPLE);
    }

    DrawLine3D(segment.ptA, segment.ptB, color);
    myDrawQuad(quad, color);
    DrawLine3D(quad.center, normal + quad.center, PURPLE);
}