#include "Sphere.h"

#include "Vector3.h"

Sphere::Sphere(const vec3& c, const float& r, const quat& q)
{
    center = c;
    radius = r;
    quaternion = q;
}

vec3 Sphere::getSphericalCoords(const float& theta, const float& phi)
{
    float x = sinf(theta) * cosf(phi);
    float y = cosf(theta);
    float z = sinf(theta) * sinf(phi);

    return { x, y, z };
}

bool Sphere::Segment_Sphere(const Segment& segment, vec3& interPt, vec3& interNormal)
{
    vec3 AB = vecFromPt(segment.ptA, segment.ptB);
    vec3 CenterA = vecFromPt(center, segment.ptA);
    
    float ABsquared = dotProduct(AB, AB);
    float dotCenterAB = dotProduct(CenterA, AB);

    float delta = (4 * (dotCenterAB * dotCenterAB)) - (4 * ABsquared * (dotProduct(CenterA, CenterA) - radius * radius));

    if (delta <= 0)
        return false;

    float T = (-2 * dotCenterAB - sqrt(delta)) / (2 * ABsquared);

    if (T <= 0 || T >= 1)
        return false;

    interPt = segment.ptA + AB * T;

    vec3 normal = interPt - center;
    interNormal = normalize(normal);

    return true;
}