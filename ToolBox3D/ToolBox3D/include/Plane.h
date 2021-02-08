#pragma once

#include "Maths.h"

struct Plane
{
	Vector3 normal;
	float direction;

	Plane() = default;
	Plane(Vector3 normal, float d);
	Plane(Vector3 normal, Vector3 pos);
	Plane(Vector3 vecA, Vector3 vecB, Vector3 vecC);

	bool Segment_Plane(const Segment& segment, Plane plane, Vector3& interPt, Vector3& interNormal);
	void myDrawPlane();
};

