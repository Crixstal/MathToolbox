#include "Plane.h"

#include "Vector3.h"

Plane::Plane(const vec3& n, const float& d)
{
	normal = normalize(n);
	distance = d;
}

Plane::Plane(const vec3& n, const vec3& pos)
{
	normal = normalize(n);
	distance = dotProduct(pos, n);
}

Plane::Plane(const vec3& vecA, const vec3& vecB, const vec3& vecC)
{
	vec3 AB = vecFromPt(vecA, vecB);
	vec3 AC = vecFromPt(vecA, vecC);

	normal = normalize(crossProduct(AB, AC));
	distance = dotProduct(vecA, normal);
}

bool Plane::Segment_Plane(const Segment& segment, vec3& interPt, vec3& interNormal)
{
	vec3 AB = vecFromPt(segment.ptA, segment.ptB);
	float dotAB_normal = dotProduct(AB, normal);

	if (fabsf(dotAB_normal) <= 1e-6)
		return false;
	
	float T = (distance - dotProduct(segment.ptA, normal)) / dotAB_normal;

	if (T < 0 || T > 1)
		return false;

	interPt = segment.ptA + AB * T;
	interNormal = normal;

	if (dotAB_normal > 0)
		interNormal = -interNormal;

	return true;
}