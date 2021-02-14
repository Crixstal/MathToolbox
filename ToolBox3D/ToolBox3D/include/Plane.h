#pragma once

#include "Maths.h"

struct Plane
{
	Vector3 normal;
	float direction;

	Plane() = default;
	Plane(const Vector3& n, const float& d);
	Plane(const Vector3& n, const Vector3& pos);
	Plane(const Vector3& vecA, const Vector3& vecB, const Vector3& vecC);

	bool Segment_Plane(const Segment& segment, Plane& plane, Vector3& interPt, Vector3& interNormal);
	void myDrawPlane(Plane& plane, const Color& color);
	void drawIntersection(const Segment& segment, Plane& plane, Vector3& interPt, Vector3& interNormal);
};