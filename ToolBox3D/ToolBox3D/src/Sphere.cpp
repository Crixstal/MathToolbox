#include "Sphere.h"

bool Sphere::Segment_Sphere(const Segment& segment, Sphere sphere, Vector3& interPt, Vector3& interNormal)
{
    Vector3 AB = vecFromPt(segment.ptA, segment.ptB);
    Vector3 CenterA = vecFromPt(sphere.center, segment.ptA);

    float ABsquared = dotProduct(AB, AB);
    float dotCenterAB = dotProduct(CenterA, AB);

    float delta = powf(dotCenterAB, 2) - 4 * ABsquared * (powf(dotProduct(CenterA, CenterA), 2) - powf(sphere.radius, 2));

    if (delta < 1e-6)
        return false;

    float T = (-2 * dotCenterAB - sqrt(delta)) / (2 * ABsquared);
    interPt = segment.ptA + AB * T;

    interNormal = normalize(interPt - sphere.center);

    return true;
}

Vector3 Sphere::getSphericalCoords(float r, float theta, float phi)
{
    float x = r * sinf(theta) * cosf(phi);
    float y = r * cosf(theta);
    float z = r * sinf(theta) * sinf(phi);

    return { x, y, z };
}

void Sphere::myDrawSphere(float lon, float lat)
{
    float r = 1.f;

    rlBegin(RL_QUADS);

    for (int j = 0; j < lat; ++j)
    {
        float theta0 = ((j + 0) / (float)lat) * M_PI;
        float theta1 = ((j + 1) / (float)lat) * M_PI;

        for (int i = 0; i < lon; ++i)
        {
            float phi0 = ((i + 0) / (float)lon) * 2.f * M_PI;
            float phi1 = ((i + 1) / (float)lon) * 2.f * M_PI;

            Vector3 c0 = getSphericalCoords(r, theta1, phi1);
            Vector3 c1 = getSphericalCoords(r, theta1, phi0);
            Vector3 c2 = getSphericalCoords(r, theta0, phi0);
            Vector3 c3 = getSphericalCoords(r, theta0, phi1);

            rlColor3f(0.f, 1.f, 0.f);

            rlVertex3f(c0.x, c0.y, c0.z);
            rlVertex3f(c1.x, c1.y, c1.z);
            rlVertex3f(c2.x, c2.y, c2.z);
            rlVertex3f(c3.x, c3.y, c3.z);
        }
    }

    rlEnd();
}