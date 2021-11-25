#include "Range.h"

#include "Vector3.h"

float Range::getMin(const float& a, const float& b)
{
    if (a < b)
        return a;
    else
        return b;
}

float Range::getMax(const float& a, const float& b)
{
    if (a > b)
        return a;
    else
        return b;
}

Range Range::globalRange(const Range& rng1, const Range& rng2)
{
    Range globalRng;

    globalRng.min = getMin(rng1.min, rng2.min);
    globalRng.max = getMax(rng1.max, rng2.max);

    return globalRng;
}

Range Range::globRngVal(const Range& rng, const float& a)
{
    Range globRngVal;

    globRngVal.min = getMin(rng.min, a);
    globRngVal.max = getMax(rng.max, a);

    return globRngVal;
}

bool Range::rangeOverlap(const Range& rng1, const Range& rng2)
{
    if (rng1.min > rng2.max || rng2.min > rng1.max)
        return false;

    return true;
}

Range Range::ptOnAxisRng(const vec3& pt, const vec3& axis)
{
    float projection = dotProduct(pt, axis);

    Range rng = { projection, projection };

    return rng;
}

Range Range::segOnAxisRng(const Segment& seg, const vec3& axis)
{
    float projectionA = dotProduct(seg.ptA, axis);
    float projectionB = dotProduct(seg.ptB, axis);

    Range rng = { getMin(projectionA, projectionB), getMax(projectionA, projectionB) };

    return rng;
}

Range Range::boxOnAxisRng(const Box& box, const vec3& axis)
{
#pragma region VECTOR
    vec3 pt1 = { box.center.x + box.size.x, box.center.y + box.size.y, box.center.z + box.size.z }; // top right back
    vec3 pt2 = { box.center.x - box.size.x, box.center.y + box.size.y, box.center.z + box.size.z }; // top left back
    vec3 pt3 = { box.center.x - box.size.x, box.center.y + box.size.y, box.center.z - box.size.z }; // top left front
    vec3 pt4 = { box.center.x + box.size.x, box.center.y + box.size.y, box.center.z - box.size.z }; // top right front

    vec3 pt5 = { box.center.x + box.size.x, box.center.y - box.size.y, box.center.z + box.size.z }; // down right back
    vec3 pt6 = { box.center.x - box.size.x, box.center.y - box.size.y, box.center.z + box.size.z }; // down left back
    vec3 pt7 = { box.center.x - box.size.x, box.center.y - box.size.y, box.center.z - box.size.z }; // down left front
    vec3 pt8 = { box.center.x + box.size.x, box.center.y - box.size.y, box.center.z - box.size.z }; // down right front
#pragma endregion

#pragma region NUM
    float num = dotProduct(axis, axis);

    float num1 = dotProduct(pt1, axis);
    float num2 = dotProduct(pt2, axis);
    float num3 = dotProduct(pt3, axis);
    float num4 = dotProduct(pt4, axis);

    float num5 = dotProduct(pt5, axis);
    float num6 = dotProduct(pt6, axis);
    float num7 = dotProduct(pt7, axis);
    float num8 = dotProduct(pt8, axis);
#pragma endregion

#pragma region MIN
    float min = getMin(num, num1);
    min = getMin(min, num2);
    min = getMin(min, num3);
    min = getMin(min, num4);

    min = getMin(min, num5);
    min = getMin(min, num6);
    min = getMin(min, num7);
    min = getMin(min, num8);
#pragma endregion

#pragma region MAX
    float max = getMax(num, num1);
    max = getMax(max, num2);
    max = getMax(max, num3);
    max = getMax(max, num4);

    max = getMax(max, num5);
    max = getMax(max, num6);
    max = getMax(max, num7);
    max = getMax(max, num8);
#pragma endregion

    Range rng = { min, max };

    return rng;
}