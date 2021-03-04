#pragma once

#include "Maths.h"

struct Quad
{
	Vector3 center;
	Quaternion quaternion;
	Vector2 extension;
	
	Quad() = default;
	Quad(const Vector3& c, const Quaternion& q, const Vector2& e);

	void myDrawQuad(const Quad& quad, Color color = GREEN);
	void drawIntersection(const Segment& segment, const Quad& quad, Vector3& interPt, Vector3& interNormal, Color color = GREEN);
};
	bool Segment_Quad(const Segment& segment, const Quad& quad, Vector3& interPt, Vector3& interNormal);

