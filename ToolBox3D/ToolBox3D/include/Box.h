#pragma once

#include "Maths.h"
#include "Quad.h"

struct Box
{
	Vector3 center;
	Vector3 size;
	Quaternion quaternion;

	Box(const Vector3& c, const Vector3& s, const Quaternion& q);

	void myDrawBox(const Vector3& center, const Vector3& size, Color color = GREEN);
	bool Segment_Box(const Segment& segment, const Box& box, Vector3& interPt, Vector3& interNormal);

	void myDrawRoundBox(const Vector3& center, const Vector3& size, Color color = GREEN);
	//bool Segment_RoundBox(const Segment& segment, const Box& box, Vector3& interPt, Vector3& interNormal);
};
