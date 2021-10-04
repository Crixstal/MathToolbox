#pragma once

#include "Maths.h"
#include "Referential.h"

struct Quad
{
	Vector3 center;
	Quaternion quaternion;
	Vector2 extension;
	
	Quad() {};
	Quad(const Vector3& c, const Quaternion& q, const Vector2& e);

	void myDrawQuad(const Color& color = GREEN);
	bool isInQuad(const Vector3& point);
	bool Segment_Quad(const Segment& segment, Vector3& interPt, Vector3& interNormal);
	void drawIntersection(const Segment& segment, Vector3& interPt, Vector3& interNormal, Color color = GREEN);
};
