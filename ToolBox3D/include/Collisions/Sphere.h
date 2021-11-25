#pragma once

#include "Definitions.h"

struct Sphere
{
	vec3 center;
	float radius;
	quat quaternion;

	Sphere(const vec3& c, const float& r, const quat& q);

	vec3 getSphericalCoords(const float& theta, const float& phi);
	bool Segment_Sphere(const Segment& segment, vec3& interPt, vec3& interNormal);
};