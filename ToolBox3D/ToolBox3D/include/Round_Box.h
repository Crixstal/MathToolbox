#pragma once

#include "Maths.h"
#include "Sphere.h"
#include "Box.h"
#include "Capsule.h"

struct Round_Box
{
	Vector3 center;
	Vector3 size;
	Quaternion quaternion;

	Round_Box(const Vector3& c, const Vector3& s, const Quaternion& q);

	void myDrawRoundBox(Color color = GREEN);
};

