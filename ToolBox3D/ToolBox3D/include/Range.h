#pragma once

#include "Box.h"

struct Range
{
	float min;
	float max;

	float getMin(const float& a, const float& b);
	float getMax(const float& a, const float& b);

	Range globalRange(const Range& rng1, const Range& rng2);
	Range globRngVal(const Range& rng, const float& a);

	bool rangeOverlap(const Range& rng1, const Range& rng2);

	//Range boxOnAxisRng(const Box& box, const Vector3& vect);
};