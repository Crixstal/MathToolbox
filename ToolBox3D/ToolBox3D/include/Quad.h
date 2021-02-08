#pragma once

#include "Maths.h"

struct Quad
{
	Vector3 center;
	Vector3 unitNormal;
	Vector2 extensions;
	
	void myDrawRectangle(Vector3 center, Vector3 unitNormal, Vector2 extensions, Color rectColor = GREEN);
	bool Segment_Quad(const Segment& segment, Quad quad, Vector3& interPt, Vector3& interNormal);
};

