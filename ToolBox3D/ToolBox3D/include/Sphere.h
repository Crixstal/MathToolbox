#pragma once

#include <raylib.h>
#include <rlgl.h>

#include "Maths.h"

struct Sphere
{
	Vector3 center;
	float radius;

	bool Segment_Sphere(const Vector3& vecA, const Vector3& vecB, Sphere sphere, Vector3& interPt, Vector3& interNormal);
	Vector3 getSphericalCoords(float r, float theta, float phi);
	void myDrawSphere(float lon, float lat);
};

