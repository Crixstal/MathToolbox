#pragma once

#include "Maths.h"

struct Sphere
{
	Vector3 center;
	float radius;

	bool Segment_Sphere(const Segment& segment, Sphere sphere, Vector3& interPt, Vector3& interNormal);
	Vector3 getSphericalCoords(float r, float theta, float phi);
	void myDrawSphere(float lon, float lat);
};

