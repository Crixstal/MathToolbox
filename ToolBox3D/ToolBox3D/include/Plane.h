#pragma once

#include "Maths.h"

struct Plane
{
	Vector3 normal;
	float distance;

	Plane(const Vector3& n, const float& d);
	Plane(const Vector3& n, const Vector3& pos);
	Plane(const Vector3& vecA, const Vector3& vecB, const Vector3& vecC);

	void myDrawPlane(Color color = GREEN);
	bool Segment_Plane(const Segment& segment, Vector3& interPt, Vector3& interNormal);
	void drawIntersection(const Segment& segment, Vector3& interPt, Vector3& interNormal, Color color = GREEN);
};