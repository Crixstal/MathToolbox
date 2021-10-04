#pragma once

#include "Maths.h"
#include "Quad.h"
#include "Referential.h"

struct Box
{
	Vector3 center;
	Vector3 size;
	Quaternion quaternion;

	Box(const Vector3& c, const Vector3& s, const Quaternion& q);

	void myDrawBox(const Color& color = GREEN);
	bool isPointInsideBox(const Vector3& point, const Box& box);
    Quad getRight() const;
	Quad getLeft() const;
	Quad getFront() const;
	Quad getBack() const;
	Quad getUp() const;
	Quad getBottom() const;
	bool Segment_Box(const Segment& segment, Vector3& interPt, Vector3& interNormal);
	void drawIntersection(const Segment& segment, Vector3& interPt, Vector3& interNormal, Color color = GREEN);
};