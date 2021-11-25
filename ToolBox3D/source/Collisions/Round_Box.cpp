#include "Round_Box.h"
#include "Box.h"

#include "Vector3.h"

Round_Box::Round_Box(const vec3& c, const vec3& s, const quat& q, const float& r)
{
    center = c;
    size = s;
    quaternion = q;
    radius = r;
}

Round_Box::operator Box() const
{
    return { center, size, quaternion };
}

bool Round_Box::isPointInsideRoundedBox(const vec3& point, const Round_Box& rBox)
{
    Box box = rBox;
    // Test if inside box, which means rounded box without radius extension
    if (box.isPointInsideBox(point))
        return true;

    // Find an intersection between point and box center, and look if the distance is bigger than radius
    vec3 interPt, interNormal;
    box.Segment_Box({ point, rBox.center }, interPt, interNormal, nullptr);

    float distanceFromBox = powf(vecMagnitude(point - interPt), 2);

    return (distanceFromBox < rBox.radius * rBox.radius);
}

bool Round_Box::Segment_RoundedBox_InsideAABB(const Segment& segment, Box& AABB, vec3& interPt, vec3& interNormal)
{
    // Method called when segment could be between rounded's AABB and rounded itself
    if (!AABB.isPointInsideBox(segment.ptA))
        return false;

    if (isPointInsideRoundedBox(segment.ptA, *this))
        return false;

    // Find 4 nearest point of the roundedBox from A point
    // These points will form 3 capsules' axis
    Box box = *this;
    vec3 localNearVertice;
    vec3 nearVertice = box.getNearVertice(segment.ptA, localNearVertice);

    vec3 oppositeVerticeX = box.boxVerticeLocalToGlobal(vec3{-localNearVertice.x, localNearVertice.y, localNearVertice.z});
    vec3 oppositeVerticeY = box.boxVerticeLocalToGlobal(vec3{localNearVertice.x, -localNearVertice.y, localNearVertice.z});
    vec3 oppositeVerticeZ = box.boxVerticeLocalToGlobal(vec3{localNearVertice.x, localNearVertice.y, -localNearVertice.z});

    bool isOnCylinder = false;

    Capsule capsToTest(nearVertice, oppositeVerticeX, radius);
    if (capsToTest.Segment_Capsule(segment, interPt, interNormal, isOnCylinder) && isOnCylinder)
        return true;

    capsToTest.ptQ = oppositeVerticeY;
    if (capsToTest.Segment_Capsule(segment, interPt, interNormal, isOnCylinder) && isOnCylinder)
        return true;

    capsToTest.ptQ = oppositeVerticeZ;
    return capsToTest.Segment_Capsule(segment, interPt, interNormal, isOnCylinder);
}

bool Round_Box::Segment_RoundBox(const Segment& segment, vec3& interPt, vec3& interNormal)
{
    Box AABB = { center, {size.x + radius, size.y + radius, size.z + radius}, quaternion};

    // First assert that segment intersect with roundedBox AABB, if not we call a different test
    Quad intersectedQuad;
    if (!AABB.Segment_Box(segment, interPt, interNormal, &intersectedQuad))
        return Segment_RoundedBox_InsideAABB(segment, AABB, interPt, interNormal);

    // Get a face of the roundedBox from the AABB intersected Quad
    intersectedQuad.extension.x -= radius;
    intersectedQuad.extension.y -= radius;

    // If there is no / /  with the quad, we get the nearest edges which will be capsule axis
    Segment nearestEdge1, nearestEdge2;
    if (intersectedQuad.isInQuad(interPt, intersectedQuad, nearestEdge1, nearestEdge2))
        return true;

    // Substract a normal vector to "translate" edge point to have correct capsules' center
    vec3 radiusNormal = interNormal * radius;
    nearestEdge1.ptA -= radiusNormal;
    nearestEdge1.ptB -= radiusNormal;
    nearestEdge2.ptA -= radiusNormal;
    nearestEdge2.ptB -= radiusNormal;

    bool isOnCylinder = false;
    Capsule capsToTest(nearestEdge1.ptA, nearestEdge1.ptB, radius);

    // If intersection's point is not on cylinder, we return the second intersection to avoid "intra-intersection"
    if (capsToTest.Segment_Capsule(segment, interPt, interNormal, isOnCylinder) && isOnCylinder)
        return true;

    capsToTest = Capsule(nearestEdge2.ptA, nearestEdge2.ptB, radius);

    return capsToTest.Segment_Capsule(segment, interPt, interNormal);
}