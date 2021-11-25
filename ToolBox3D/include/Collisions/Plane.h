#pragma once

#include "Definitions.h"

struct Plane
{
	vec3 normal;
	float distance;

	Plane(const vec3& n, const float& d);
	Plane(const vec3& n, const vec3& pos);
	Plane(const vec3& vecA, const vec3& vecB, const vec3& vecC);

	bool Segment_Plane(const Segment& segment, vec3& interPt, vec3& interNormal);
};