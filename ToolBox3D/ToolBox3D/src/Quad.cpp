#include "Quad.h"
#include "Plane.h"

Quad::Quad(const Vector3& c, const Quaternion& q, const Vector2& e)
{
    center = c;
    quaternion = q;
    extension = e;
}

void Quad::myDrawQuad(const Color& color)
{
    rlPushMatrix();
    rlTranslatef(center.x, center.y, center.z);

    Vector3 vect;
    float angle;
    QuaternionToAxisAngle(quaternion, &vect, &angle);
    rlRotatef(angle * RAD2DEG, vect.x, vect.y, vect.z);

    rlScalef(extension.x, 1.0f, extension.y);

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

bool Quad::isInQuad(const Vector3& point)
{
    // Test in local referentiel to simplify calcul by only compare quad extension with point coordinates
    Referential localRef (center, quaternion);

    Vector3 localPoint = point;
    localRef.globToLocPos(localRef, localPoint);

    return (fabsf(localPoint.x) <= extension.x) && (fabsf(localPoint.z) <= extension.y);
}

bool Quad::Segment_Quad(const Segment& segment, Vector3& interPt, Vector3& interNormal)
{
    Vector3 normal = normalize(Vector3RotateByQuaternion({ 0.0f, 1.0f, 0.0f }, quaternion));

    Plane plane (normal, center);

    if (!plane.Segment_Plane(segment, interPt, interNormal))
        return false;

    return isInQuad(interPt);
}

void Quad::drawIntersection(const Segment& segment, Vector3& interPt, Vector3& interNormal, Color color)
{
    Vector3 normal = normalize(Vector3RotateByQuaternion({ 0.0f, 1.0f, 0.0f }, quaternion));

    if (Segment_Quad(segment, interPt, interNormal))
    {
        color = RED;
        DrawSphere(interPt, 0.08f, BROWN);
        DrawLine3D(interPt, interNormal + interPt, PURPLE);
    }

    DrawLine3D(segment.ptA, segment.ptB, color);
    myDrawQuad(color);
    DrawLine3D(center, normal + center, PURPLE);
}