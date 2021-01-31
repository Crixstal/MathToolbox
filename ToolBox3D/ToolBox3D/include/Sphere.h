#pragma once

#include <raylib.h>

#include "Maths.h"

struct Sphere
{
	Vector3 center;
	float radius;

	bool Segment_Sphere(const Vector3& vecA, const Vector3& vecB, Sphere sphere, Vector3& interPt, Vector3& interNormal);
	void drawSphere();
};

