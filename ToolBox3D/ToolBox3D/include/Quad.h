#pragma once

#include "Maths.h"

struct Quad
{
	Vector3 center;
	Vector3 unitNormal;
	Vector3 size;
	
	void myDrawQuad(Vector3 center, Vector3 size, Quaternion quaternion, Color color = GREEN);
	bool Segment_Quad(const Segment& segment, Quad quad, Vector3& interPt, Vector3& interNormal);
};

