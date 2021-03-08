#pragma once

#include "Maths.h"
#include "Quad.h"

struct Box
{
	Vector3 center;
	Vector3 size;
	Quaternion quaternion;

	Box(const Vector3& c, const Vector3& s, const Quaternion& q);

	void myDrawBox(const Color& color = GREEN);
	bool Segment_Box(const Segment& segment, Vector3& interPt, Vector3& interNormal);
	void drawIntersection(const Segment& segment, Vector3& interPt, Vector3& interNormal, Color color = GREEN);
};