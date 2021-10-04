#include "Round_Box.h"

Round_Box::Round_Box(const Vector3& c, const Vector3& s, const Quaternion& q)
{
    center = c;
    size = s;
    quaternion = q;
}

void Round_Box::myDrawRoundBox(const Color& color)
{
#pragma region SPHERE
    Sphere sphere1({ center.x - 1.0f, center.y + 1.0f, center.z + 1.0f }, 0.5f); // front up left
    Sphere sphere2({ center.x + 1.0f, center.y + 1.0f, center.z + 1.0f }, 0.5f); // front up right
    Sphere sphere3({ center.x + 1.0f, center.y - 1.0f, center.z + 1.0f }, 0.5f); // front down right
    Sphere sphere4({ center.x - 1.0f, center.y - 1.0f, center.z + 1.0f }, 0.5f); // front down left

    Sphere sphere5({ center.x + 1.0f, center.y + 1.0f, center.z - 1.0f }, 0.5f); // back up right
    Sphere sphere6({ center.x - 1.0f, center.y + 1.0f, center.z - 1.0f }, 0.5f); // back up left
    Sphere sphere7({ center.x + 1.0f, center.y - 1.0f, center.z - 1.0f }, 0.5f); // back down right
    Sphere sphere8({ center.x - 1.0f, center.y - 1.0f, center.z - 1.0f }, 0.5f); // back down left

    sphere1.myDrawSphere(20, 20, PI / 2, 0, PI, PI / 2, color); // startLong, startLat, endLong, endLat
    sphere2.myDrawSphere(20, 20, 0, 0, PI / 2, PI / 2, color);
    sphere3.myDrawSphere(20, 20, 0, PI / 2, PI / 2, PI, color);
    sphere4.myDrawSphere(20, 20, PI / 2, PI, PI, PI / 2, color);

    sphere5.myDrawSphere(20, 20, 3 * PI / 2, 0, 2 * PI, PI / 2, color);
    sphere6.myDrawSphere(20, 20, 0, 3 * PI / 2, PI / 2, 2 * PI, color);
    sphere7.myDrawSphere(20, 20, 3 * PI / 2, PI / 2, 2 * PI, PI, color);
    sphere8.myDrawSphere(20, 20, PI, PI / 2, 3 * PI / 2, PI, color);
#pragma endregion

#pragma region CYLINDER
    float r = 0.25/2; //radius cylinder / 2;

    Cylinder cyl1(sphere2.center, sphere1.center, 0.5f, true); // front up
    Cylinder cyl2(sphere4.center, sphere3.center, 0.5f, true); // front down
    Cylinder cyl3(sphere3.center, sphere2.center, 0.5f, true); // front right
    Cylinder cyl4(sphere4.center, sphere1.center, 0.5f, true); // front left

    Cylinder cyl5({ -1 + r,1.5f,0 }, { 1 - r,1.5f,0 }, 0.5f, true);
    Cylinder cyl6({ 1,1.5f,0 + r }, { 1,1.5f,2 - r }, 0.5f, true);
    Cylinder cyl7({ 1 - r,1.5f,2 }, { -1 + r,1.5f,2 }, 0.5f, true);
    Cylinder cyl8({ -1,1.5f,2 - r }, { -1,1.5f,0 + r }, 0.5f, true);

    cyl1.myDrawCylinder(color, 20, 0, PI / 2);
    cyl2.myDrawCylinder(color, 20, 0, PI / 2);
    cyl3.myDrawCylinder(color, 20, 0, PI / 2);
    cyl4.myDrawCylinder(color, 20, 3 * PI / 2, 2 * PI);
    //cyl5.myDrawCylinder(color, 20);
    //cyl6.myDrawCylinder(color, 20);
    //cyl7.myDrawCylinder(color, 20);
    //cyl8.myDrawCylinder(color, 20);
#pragma endregion
}

bool Round_Box::Segment_RoundBox(const Segment& segment, Vector3& interPt, Vector3& interNormal)
{
    return true;
}

void Round_Box::drawIntersection(const Segment& segment, Vector3& interPt, Vector3& interNormal, Color color)
{
    Vector3 normal = normalize(Vector3RotateByQuaternion({ 0.0f, 1.0f, 0.0f }, quaternion));

    /*if (Segment_RoundBox(segment, interPt, interNormal))
    {
        color = RED;
        DrawSphere(interPt, 0.08f, BROWN);
        DrawLine3D(interPt, interNormal + interPt, PURPLE);
    }*/

    DrawLine3D(segment.ptA, segment.ptB, color);
    myDrawRoundBox(color);
    DrawLine3D(center, 2.0f * normal + center, PURPLE);
}