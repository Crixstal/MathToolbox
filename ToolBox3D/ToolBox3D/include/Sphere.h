#pragma once

#include "Maths.h"

struct Sphere
{
	Vector3 center;
	float radius;
	Quaternion quaternion;

	Sphere(const Vector3& c, const float& r, const Quaternion& q);

	Vector3 getSphericalCoords(const float& theta, const float& phi);
	void myDrawSphere(const int& resLong, const int& resLat, const float& startLong = 0, const float& startLat = 0, const float& endLong = 2 * PI, const float& endLat = PI, const Color& color = GREEN);
	bool Segment_Sphere(const Segment& segment, Vector3& interPt, Vector3& interNormal);
	void drawIntersection(const Segment& segment, const int& resLong, const int& resLat, Vector3& interPt, Vector3& interNormal, Color color = GREEN);
};