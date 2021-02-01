#include "Sphere.h"

bool Sphere::Segment_Sphere(const Vector3& vecA, const Vector3& vecB, Sphere sphere, Vector3& interPt, Vector3& interNormal)
{
    Vector3 AB = vecB - vecA;
    Vector3 CenterA = vecA - sphere.center;

    float ABsquared = dotProduct(AB, AB);
    float dotCenterAB = dotProduct(CenterA, AB);

    float delta = powf(dotCenterAB, 2) - 4 * ABsquared * (powf(dotProduct(CenterA, CenterA), 2) - powf(sphere.radius, 2));

    if (delta < 1e-6)
        return false;

    float T = (-2 * dotCenterAB - sqrt(delta)) / (2 * ABsquared);
    interPt = vecA + AB * T;

    interNormal = normalize(interPt - sphere.center);

    return true;
}

void Sphere::drawSphere()
{
    DrawSphere({0, 0, 0}, 3, GREEN);
}