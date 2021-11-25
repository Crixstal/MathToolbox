#include "Quad.h"
#include "Plane.h"

Quad::Quad(const vec3& c, const quat& q, const vec2& e)
{
    center = c;
    quaternion = q;
    extension = e;
}

vec3 Quad::getNearVertice(const vec3& localPt, const Quad& quad)
{
    return {
        localPt.x < 0.f ? -quad.extension.x : quad.extension.x,
        0.f,
        localPt.z < 0.f ? -quad.extension.y : quad.extension.y, };
}

Segment Quad::getNearEdge(const vec3& externLocalPt)
{
    Segment nearestSeg;

    if (externLocalPt.x < -extension.x / 2)
        nearestSeg = { vec3{-extension.x / 2, 0.f, extension.y / 2}, vec3{-extension.x / 2, 0.f, -extension.y / 2} };

    else if (externLocalPt.x > extension.x / 2)
        nearestSeg = { vec3{extension.x / 2, 0.f, extension.y / 2}, vec3{extension.x / 2, 0.f, -extension.y / 2} };

    else if (externLocalPt.z > extension.y / 2)
        nearestSeg = { vec3{-extension.x / 2, 0.f, -extension.y / 2}, vec3{extension.x / 2, 0.f, -extension.y / 2} };

    else if (externLocalPt.z > extension.y / 2)
        nearestSeg = { vec3{-extension.x / 2, 0.f, extension.y / 2}, vec3{extension.x / 2, 0.f, extension.y / 2} };

    return nearestSeg;
}

bool Quad::isInQuad(const vec3& point)
{
    Referential localRef(center, quaternion);

    vec3 localPoint = point;
    localRef.globToLocPos(localRef, localPoint);

    return (fabsf(localPoint.x) <= extension.x) && (fabsf(localPoint.z) <= extension.y);
}

bool Quad::isInQuad(const vec3& point, const Quad& quad, Segment& nearestEgde1, Segment& nearestEgde2)
{
    // As the precedent method but stock the 3 nearest vertices of the quad from the point

    Referential localRef(center, quaternion);

    vec3 localPoint = point;
    localRef.globToLocPos(localRef, localPoint);

    vec3 nearestVertice = getNearVertice(localPoint, quad);
    localRef.locToGlobPos(localRef, nearestVertice);

    // Take a symetric point by change sign of X
    nearestEgde1.ptA = nearestVertice;
    nearestEgde1.ptB = getNearVertice(vec3{ -localPoint.x - 0.001f, localPoint.y, localPoint.z }, quad);
    localRef.locToGlobPos(localRef, nearestEgde1.ptB);

    // Take a symetric point by change sign of X
    nearestEgde2.ptA = nearestVertice;
    nearestEgde2.ptB = getNearVertice(vec3{localPoint.x, localPoint.y, -localPoint.z - 0.001f}, quad);
    localRef.locToGlobPos(localRef, nearestEgde2.ptB);

    return (fabsf(localPoint.x) <= quad.extension.x) && (fabsf(localPoint.z) <= quad.extension.y);
}

bool Quad::Segment_Quad(const Segment& segment, vec3& interPt, vec3& interNormal)
{
    vec3 normal = normalize(rotateByQuat(vec3(0.0f, 1.0f, 0.0f), quaternion));

    Plane plane (normal, center);

    if (!plane.Segment_Plane(segment, interPt, interNormal))
        return false;

    return isInQuad(interPt);
}