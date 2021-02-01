#pragma once

#include <raylib.h>
#include <rlgl.h>

#include "Maths.h"

struct Plane
{
	Vector3 normal;
	float direction;

	Plane() = default;
	Plane(Vector3 normal, float d);
	Plane(Vector3 normal, Vector3 pos);
	Plane(Vector3 vecA, Vector3 vecB, Vector3 vecC);

	bool Segment_Plane(const Vector3& vecA, const Vector3& vecB, Plane plane, Vector3& interPt, Vector3& interNormal);
	void myDrawPlane();
};

