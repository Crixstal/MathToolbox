#pragma once

#include "Maths.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Capsule.h"

struct Box;

struct Round_Box
{
	Vector3 center;
	Vector3 size;
	Quaternion quaternion;
	float radius;

	Round_Box(const Vector3& c, const Vector3& s, const Quaternion& q, const float& r);

	operator Box() const;

	void myDrawRoundBox(const Color& color = GREEN);	
	bool isPointInsideRoundedBox(const Vector3& point, const Round_Box& rBox);
	bool Segment_RoundBox(const Segment& segment, Vector3& interPt, Vector3& interNormal);
	bool Segment_RoundedBox_InsideAABB(const Segment& segment, Box& AABB, Vector3& interPt, Vector3& interNormal);
	void drawIntersection(const Segment& segment, Vector3& interPt, Vector3& interNormal, Color color = GREEN);
};

