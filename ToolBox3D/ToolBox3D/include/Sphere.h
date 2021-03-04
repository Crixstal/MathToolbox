#pragma once

#include "Maths.h"

struct Sphere
{
	Vector3 center;
	float radius;

	Sphere(const Vector3& c, const float& r);

	Vector3 getSphericalCoords(const float& theta, const float& phi);
	void myDrawSphere(const int& resLong, const int& resLat, const float& startLong = 0, const float& startLat = 0, const float& endLong = 2 * PI, const float& endLat = PI, Color color = GREEN);
	static bool Segment_Sphere(const Segment& segment, const Sphere& sphere, Vector3& interPt, Vector3& interNormal);
	void drawIntersection(const Segment& segment, const Sphere& sphere, const int& resLong, const int& resLat, Vector3& interPt, Vector3& interNormal, Color color = GREEN);
};