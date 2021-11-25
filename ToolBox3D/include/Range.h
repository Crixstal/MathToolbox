#pragma once

#include "Box.h"
#include "Definitions.h"

struct Range
{
	float min;
	float max;

	float getMin(const float& a, const float& b);
	float getMax(const float& a, const float& b);

	Range globalRange(const Range& rng1, const Range& rng2);
	Range globRngVal(const Range& rng, const float& a);

	bool rangeOverlap(const Range& rng1, const Range& rng2);

	Range ptOnAxisRng(const vec3& pt, const vec3& axis);
	Range segOnAxisRng(const Segment& seg, const vec3& axis);
	Range boxOnAxisRng(const Box& box, const vec3& axis);
};