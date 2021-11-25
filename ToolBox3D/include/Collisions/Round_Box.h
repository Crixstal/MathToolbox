#pragma once

#include "Definitions.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Capsule.h"

struct Box;

struct Round_Box
{
	vec3 center;
	vec3 size;
	quat quaternion;
	float radius;

	Round_Box(const vec3& c, const vec3& s, const quat& q, const float& r);

	operator Box() const;

	bool isPointInsideRoundedBox(const vec3& point, const Round_Box& rBox);
	bool Segment_RoundBox(const Segment& segment, vec3& interPt, vec3& interNormal);
	bool Segment_RoundedBox_InsideAABB(const Segment& segment, Box& AABB, vec3& interPt, vec3& interNormal);
};

