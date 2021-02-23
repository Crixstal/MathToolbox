#pragma once

#include "Maths.h"

struct Quad
{
	Vector3 center = {};
	Vector3 unitNormal = { 2.0f, 2.0f, 2.0f };
	Vector3 size = { 1.0f, 1.0f, 1.0f };
	
	void myDrawQuad(const Vector3& center, const Vector3& size, const Quaternion& quaternion, Color color = GREEN);
	bool Segment_Quad(const Segment& segment, const Quad& quad, Vector3& interPt, Vector3& interNormal);
};

