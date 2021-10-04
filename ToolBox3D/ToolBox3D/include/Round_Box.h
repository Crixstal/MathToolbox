#pragma once

#include "Maths.h"
#include "Sphere.h"
#include "Cylinder.h"

struct Round_Box
{
	Vector3 center;
	Vector3 size;
	Quaternion quaternion;

	Round_Box(const Vector3& c, const Vector3& s, const Quaternion& q);

	void myDrawRoundBox(const Color& color = GREEN);	
	bool Segment_RoundBox(const Segment& segment, Vector3& interPt, Vector3& interNormal);
	void drawIntersection(const Segment& segment, Vector3& interPt, Vector3& interNormal, Color color = GREEN);
};

