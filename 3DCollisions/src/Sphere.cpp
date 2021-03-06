#include "Sphere.h"

Sphere::Sphere(const Vector3& c, const float& r, const Quaternion& q)
{
    center = c;
    radius = r;
    quaternion = q;
}

Vector3 Sphere::getSphericalCoords(const float& theta, const float& phi)
{
    float x = sinf(theta) * cosf(phi);
    float y = cosf(theta);
    float z = sinf(theta) * sinf(phi);

    return { x, y, z };
}

void Sphere::myDrawSphere(const int& resLong, const int& resLat, const float& startLong, const float& startLat, const float& endLong, const float& endLat, const Color& color)
{
    float stepLat = (endLat - startLat) / (float)resLat;
    float stepLong = (endLong - startLong) / (float)resLong;

    rlPushMatrix();

    rlTranslatef(center.x, center.y, center.z);

    Vector3 vect;
    float angle;
    QuaternionToAxisAngle(quaternion, &vect, &angle);
    rlRotatef(angle * RAD2DEG, vect.x, vect.y, vect.z);

    rlScalef(radius, radius, radius);
    rlBegin(RL_QUADS);

    rlColor4ub(color.r, color.g, color.b, color.a);

    for (int j = 0; j < resLat; ++j)
    {
        float theta0 = j * stepLat + startLat;
        float theta1 = (j + 1 == resLat) ? endLat : (j + 1) * stepLat + startLat;

        for (int i = 0; i < resLong; ++i)
        {
            float phi0 = i * stepLong + startLong;
            float phi1 = (i + 1 == resLong) ? endLong : (i + 1) * stepLong + startLong;

            Vector3 c0 = getSphericalCoords(theta1, phi1);
            Vector3 c1 = getSphericalCoords(theta1, phi0);
            Vector3 c2 = getSphericalCoords(theta0, phi0);
            Vector3 c3 = getSphericalCoords(theta0, phi1);

            rlVertex3f(c0.x, c0.y, c0.z);
            rlVertex3f(c1.x, c1.y, c1.z);
            rlVertex3f(c2.x, c2.y, c2.z);
            rlVertex3f(c3.x, c3.y, c3.z);
        }
    }

    rlEnd();
    rlPopMatrix();
}

bool Sphere::Segment_Sphere(const Segment& segment, Vector3& interPt, Vector3& interNormal)
{
    Vector3 AB = vecFromPt(segment.ptA, segment.ptB);
    Vector3 CenterA = vecFromPt(center, segment.ptA);
    
    float ABsquared = dotProduct(AB, AB);
    float dotCenterAB = dotProduct(CenterA, AB);

    float delta = (4 * (dotCenterAB * dotCenterAB)) - (4 * ABsquared * (dotProduct(CenterA, CenterA) - radius * radius));

    if (delta <= 0)
        return false;

    float T = (-2 * dotCenterAB - sqrt(delta)) / (2 * ABsquared);

    if (T <= 0 || T >= 1)
        return false;

    interPt = segment.ptA + AB * T;

    Vector3 normal = interPt - center;
    interNormal = normalize(normal);

    return true;
}

void Sphere::drawIntersection(const Segment& segment, const int& resLong, const int& resLat, Vector3& interPt, Vector3& interNormal, Color color)
{
    if (Segment_Sphere(segment, interPt, interNormal))
    {
        color = RED;
        DrawSphere(interPt, 0.08f, BROWN);
        DrawLine3D(interPt, interNormal + interPt, PURPLE);
    }

    DrawLine3D(segment.ptA, segment.ptB, color);
    myDrawSphere(resLong, resLat, 0, 0, 2 * PI, PI, color);
}