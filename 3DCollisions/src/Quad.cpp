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

Vector3 Quad::getNearVertice(const Vector3& localPt, const Quad& quad)
{
    return {
        localPt.x < 0.f ? -quad.extension.x : quad.extension.x,
        0.f,
        localPt.z < 0.f ? -quad.extension.y : quad.extension.y, };
}

Segment Quad::getNearEdge(const Vector3& externLocalPt)
{
    Segment nearestSeg;

    if (externLocalPt.x < -extension.x / 2)
        nearestSeg = { Vector3{-extension.x / 2, 0.f, extension.y / 2}, Vector3{-extension.x / 2, 0.f, -extension.y / 2} };

    else if (externLocalPt.x > extension.x / 2)
        nearestSeg = { Vector3{extension.x / 2, 0.f, extension.y / 2}, Vector3{extension.x / 2, 0.f, -extension.y / 2} };

    else if (externLocalPt.z > extension.y / 2)
        nearestSeg = { Vector3{-extension.x / 2, 0.f, -extension.y / 2}, Vector3{extension.x / 2, 0.f, -extension.y / 2} };

    else if (externLocalPt.z > extension.y / 2)
        nearestSeg = { Vector3{-extension.x / 2, 0.f, extension.y / 2}, Vector3{extension.x / 2, 0.f, extension.y / 2} };

    return nearestSeg;
}

bool Quad::isInQuad(const Vector3& point)
{
    Referential localRef(center, quaternion);

    Vector3 localPoint = point;
    localRef.globToLocPos(localRef, localPoint);

    return (fabsf(localPoint.x) <= extension.x) && (fabsf(localPoint.z) <= extension.y);
}

bool Quad::isInQuad(const Vector3& point, const Quad& quad, Segment& nearestEgde1, Segment& nearestEgde2)
{
    // As the precedent method but stock the 3 nearest vertices of the quad from the point

    Referential localRef(center, quaternion);

    Vector3 localPoint = point;
    localRef.globToLocPos(localRef, localPoint);

    Vector3 nearestVertice = getNearVertice(localPoint, quad);
    localRef.locToGlobPos(localRef, nearestVertice);

    // Take a symetric point by change sign of X
    nearestEgde1.ptA = nearestVertice;
    nearestEgde1.ptB = getNearVertice(Vector3{ -localPoint.x - 0.001f, localPoint.y, localPoint.z }, quad);
    localRef.locToGlobPos(localRef, nearestEgde1.ptB);

    // Take a symetric point by change sign of X
    nearestEgde2.ptA = nearestVertice;
    nearestEgde2.ptB = getNearVertice(Vector3{localPoint.x, localPoint.y, -localPoint.z - 0.001f}, quad);
    localRef.locToGlobPos(localRef, nearestEgde2.ptB);

    return (fabsf(localPoint.x) <= quad.extension.x) && (fabsf(localPoint.z) <= quad.extension.y);
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