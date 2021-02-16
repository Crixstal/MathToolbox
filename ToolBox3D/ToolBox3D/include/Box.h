#pragma once

#include "Maths.h"
#include "Quad.h"

struct Box
{
	Vector3 center;
	Vector3 size;
	Quaternion q = QuaternionIdentity();

	void myDrawBox(const Vector3& center, const Vector3& size, const Color& color = GREEN);
	bool Segment_Box(const Segment& segment, Box box, Vector3& interPt, Vector3& interNormal);

	void myDrawRoundBox(const Vector3& center, const Vector3& size, const Color& color = GREEN);
	//bool Segment_RoundBox(const Segment& segment, Box box, Vector3& interPt, Vector3& interNormal);
};
