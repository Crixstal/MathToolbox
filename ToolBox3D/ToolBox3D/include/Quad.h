#pragma once

#include <raylib.h>
#include <rlgl.h>

struct Quad
{
	Vector3 center;
	float halfHeight;
	float halfWidth;

	void myDrawRectangle(Vector3 center, Vector3 unitNormal, Vector2 extensions, Color rectColor = LIGHTGRAY);
	bool Segment_Quad(const Vector3& vecA, const Vector3& vecB, Quad quad, Vector3& interPt, Vector3& interNormal);
};

