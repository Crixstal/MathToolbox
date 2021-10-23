#include "Round_Box.h"
#include "Box.h"

Round_Box::Round_Box(const Vector3& c, const Vector3& s, const Quaternion& q, const float& r)
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

void Round_Box::myDrawRoundBox(const Color& color)
{
    rlPushMatrix();

    rlTranslatef(center.x, center.y, center.z);

    Vector3 vect;
    float angle;
    QuaternionToAxisAngle(quaternion, &vect, &angle);
    rlRotatef(angle * RAD2DEG, vect.x, vect.y, vect.z);

#pragma region FACES
    Quad quad1({ 0.f, radius + size.y, 0.f }, QuaternionFromAxisAngle({ 1.f, 0.f, 0.f }, 0.f), { size.x, size.z });
    Quad quad2({0.f, -radius - size.y, 0.f}, QuaternionFromAxisAngle({ 1.f, 0.f, 0.f }, PI), {size.x, size.z});
    Quad quad3({radius + size.x, 0.f, 0.f}, QuaternionFromAxisAngle({ 0.f, 0.f, 1.f }, -PI / 2.f), {size.y, size.z});
    Quad quad4({-radius - size.x, 0.f, 0.f}, QuaternionFromAxisAngle({ 0.f, 0.f, 1.f }, PI / 2.f), {size.y, size.z});
    Quad quad5({0.f, 0.f, radius + size.z}, QuaternionFromAxisAngle({ 1.f, 0.f, 0.f }, PI / 2.f), {size.x, size.y});
    Quad quad6({0.f, 0.f, -radius - size.z}, QuaternionFromAxisAngle({ 1.f, 0.f, 0.f }, -PI / 2.f), {size.x, size.y});

    quad1.myDrawQuad(color);
    quad2.myDrawQuad(color);
    quad3.myDrawQuad(color);
    quad4.myDrawQuad(color);
    quad5.myDrawQuad(color);
    quad6.myDrawQuad(color);
#pragma endregion

#pragma region ARETES
    Cylinder cyl1({ -size.x, size.y, -size.z }, { size.x, size.y, -size.z }, radius, true, QuaternionFromAxisAngle({ 0.f, 1.f, 0.f }, PI / 2.f));
    Cylinder cyl2({size.x, size.y, -size.z}, {size.x, size.y, size.z}, radius, true, QuaternionIdentity()); // BACK BOTTOM
    Cylinder cyl3({-size.x, size.y, size.z}, {size.x, size.y, size.z}, radius, true, QuaternionFromAxisAngle({ 0.f, 1.f, 0.f }, PI / 2.f)); // FRONT UP
    Cylinder cyl4({-size.x, size.y, -size.z}, {-size.x, size.y, size.z}, radius, true, QuaternionIdentity()); // LEFT UP
    Cylinder cyl5({-size.x, -size.y, -size.z}, {size.x, -size.y, -size.z}, radius, true, QuaternionFromAxisAngle({ 0.f, 1.f, 0.f }, PI / 2.f)); // RIGHT UP
    Cylinder cyl6({size.x, -size.y, -size.z}, {size.x, -size.y, size.z}, radius, true, QuaternionIdentity()); // RIGHT BOTTOM
    Cylinder cyl7({-size.x, -size.y, size.z}, {size.x, -size.y, size.z}, radius, true, QuaternionFromAxisAngle({0.f, 1.f, 0.f}, PI / 2.f)); // FRONT BOTTOM
    Cylinder cyl8({-size.x, -size.y, -size.z}, {-size.x, -size.y, size.z}, radius, true, QuaternionIdentity()); // LEFT BOTTOM
    Cylinder cyl9({-size.x, size.y, size.z}, {-size.x, -size.y, size.z}, radius, true, QuaternionFromAxisAngle({1.f, 0.f, 0.f}, PI / 2.f)); // FRONT LEFT
    Cylinder cyl10({-size.x, size.y, -size.z}, {-size.x, -size.y, -size.z},  radius, true, QuaternionFromAxisAngle({1.f, 0.f, 0.f}, PI / 2.f)); // LEFT LEFT
    Cylinder cyl11({size.x, size.y, size.z}, {size.x, -size.y, size.z}, radius, true, QuaternionFromAxisAngle({1.f, 0.f, 0.f}, PI / 2.f)); // RIGHT LEFT
    Cylinder cyl12({size.x, size.y, -size.z}, {size.x, -size.y, -size.z}, radius, true, QuaternionFromAxisAngle({1.f, 0.f, 0.f}, PI / 2.f)); // RIGHT RIGHT

    
    cyl1.myDrawCylinder(color, 20, PI, 3.f * PI / 2.f); // up back
    cyl2.myDrawCylinder(color, 20, PI / 2.f, PI); // up right
    cyl3.myDrawCylinder(color, 20, 3.f * PI / 2.f, 2 * PI); // up front
    cyl4.myDrawCylinder(color, 20, PI, 3.f * PI / 2.f); // up left

    cyl5.myDrawCylinder(color, 20, PI / 2.f, PI); // down back
    cyl6.myDrawCylinder(color, 20, 0.f, PI / 2.f); // down right
    cyl7.myDrawCylinder(color, 20, 0.f, PI / 2.f); // down front
    cyl8.myDrawCylinder(color, 20, 3.f * PI / 2.f, 2 * PI); // down left

    //MIDDLE
    cyl10.myDrawCylinder(color, 20, 0.f, PI / 2.f);
    cyl9.myDrawCylinder(color, 20, PI / 2.f, PI);
    cyl12.myDrawCylinder(color, 20, 3.f * PI / 2.f, 2 * PI);
    cyl11.myDrawCylinder(color, 20, PI, 3.f * PI / 2.f);
#pragma endregion

#pragma region VERTICES
    Sphere sphere1({ size.x, size.y, size.z }, radius, QuaternionIdentity());
    Sphere sphere2({ -size.x, size.y, size.z }, radius, QuaternionIdentity());
    Sphere sphere3({ -size.x, size.y, -size.z }, radius, QuaternionIdentity());
    Sphere sphere4({ size.x, size.y, -size.z }, radius, QuaternionIdentity());

    Sphere sphere5({ size.x, -size.y, size.z }, radius, QuaternionIdentity());
    Sphere sphere6({ -size.x, -size.y, size.z }, radius, QuaternionIdentity());
    Sphere sphere7({ -size.x, -size.y, -size.z }, radius, QuaternionIdentity());
    Sphere sphere8({ size.x, -size.y, -size.z }, radius, QuaternionIdentity());

    // UP
    sphere1.myDrawSphere(20, 20, 0.f, 0.f, PI / 2.f, PI / 2.f, color); // startLong, startLat, endLong, endLat
    sphere2.myDrawSphere(20, 20, PI / 2.f, 0.f, PI, PI / 2.f, color);
    sphere3.myDrawSphere(20, 20, 0, 3 * PI / 2, PI / 2, 2 * PI, color);
    sphere4.myDrawSphere(20, 20, 3 * PI / 2, 0, 2 * PI, PI / 2, color);

    // DOWN
    sphere5.myDrawSphere(20, 20, 0.f, PI / 2.f, PI / 2.f, PI, color);
    sphere6.myDrawSphere(20, 20, PI / 2.f, PI / 2.f, PI, PI, color);
    sphere7.myDrawSphere(20, 20, PI, PI / 2.f, 3.f * PI / 2.f, PI, color);
    sphere8.myDrawSphere(20, 20, 3.f * PI / 2.f, PI / 2.f, PI * 2, PI, color);
#pragma endregion

    rlPopMatrix();
}

bool Round_Box::isPointInsideRoundedBox(const Vector3& point, const Round_Box& rBox)
{
    Box box = rBox;
    // Test if inside box, which means rounded box without radius extension
    if (box.isPointInsideBox(point))
        return true;

    // Find an intersection between point and box center, and look if the distance is bigger than radius
    Vector3 interPt, interNormal;
    box.Segment_Box({ point, rBox.center }, interPt, interNormal, nullptr);

    float distanceFromBox = powf(vectorMagnitude(point - interPt), 2);

    return (distanceFromBox < rBox.radius * rBox.radius);
}

bool Round_Box::Segment_RoundedBox_InsideAABB(const Segment& segment, Box& AABB, Vector3& interPt, Vector3& interNormal)
{
    // Method called when segment could be between rounded's AABB and rounded itself
    if (!AABB.isPointInsideBox(segment.ptA))
        return false;

    if (isPointInsideRoundedBox(segment.ptA, *this))
        return false;

    // Find 4 nearest point of the roundedBox from A point
    // These points will form 3 capsules' axis
    Box box = *this;
    Vector3 localNearVertice;
    Vector3 nearVertice = box.getNearVertice(segment.ptA, localNearVertice);

    Vector3 oppositeVerticeX = box.boxVerticeLocalToGlobal(Vector3{-localNearVertice.x, localNearVertice.y, localNearVertice.z});
    Vector3 oppositeVerticeY = box.boxVerticeLocalToGlobal(Vector3{localNearVertice.x, -localNearVertice.y, localNearVertice.z});
    Vector3 oppositeVerticeZ = box.boxVerticeLocalToGlobal(Vector3{localNearVertice.x, localNearVertice.y, -localNearVertice.z});

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

bool Round_Box::Segment_RoundBox(const Segment& segment, Vector3& interPt, Vector3& interNormal)
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
    Vector3 radiusNormal = interNormal * radius;
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

void Round_Box::drawIntersection(const Segment& segment, Vector3& interPt, Vector3& interNormal, Color color)
{
    Vector3 normal = normalize(Vector3RotateByQuaternion({ 0.0f, 1.0f, 0.0f }, quaternion));

    if (Segment_RoundBox(segment, interPt, interNormal))
    {
        color = RED;
        DrawSphere(interPt, 0.08f, BROWN);
        DrawLine3D(interPt, interNormal + interPt, PURPLE);
    }

    DrawLine3D(segment.ptA, segment.ptB, color);
    myDrawRoundBox(color);
    DrawLine3D(center, 2.0f * normal + center, PURPLE);
}