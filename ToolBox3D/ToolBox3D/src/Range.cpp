#include "Range.h"

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

/*Range Range::boxOnAxisRng(const Box& box, const Vector3& vect)
{
#pragma region VECTOR
    Vector3 pt1 = { box.center.x + box.size.x, box.center.y + box.size.y,  box.center.z + box.size.z }; // top right back
    Vector3 pt2 = { box.center.x - box.size.x, box.center.y + box.size.y, box.center.z + box.size.z }; // top left back
    Vector3 pt3 = { box.center.x - box.size.x, box.center.y + box.size.y, box.center.z - box.size.z }; // top left front
    Vector3 pt4 = { box.center.x + box.size.x, box.center.y + box.size.y, box.center.z - box.size.z }; // top right front

    Vector3 pt5 = { box.center.x + box.size.x, box.center.y - box.size.y,  box.center.z + box.size.z }; // down right back
    Vector3 pt6 = { box.center.x - box.size.x, box.center.y - box.size.y, box.center.z + box.size.z }; // down left back
    Vector3 pt7 = { box.center.x - box.size.x, box.center.y - box.size.y, box.center.z - box.size.z }; // down left front
    Vector3 pt8 = { box.center.x + box.size.x, box.center.y - box.size.y, box.center.z - box.size.z }; // down right front
#pragma endregion

#pragma region NUM
    float num = dotProduct(vect, vect);

    float num1 = dotProduct(pt1, vect);
    float num2 = dotProduct(pt2, vect);
    float num3 = dotProduct(pt3, vect);
    float num4 = dotProduct(pt4, vect);

    float num5 = dotProduct(pt5, vect);
    float num6 = dotProduct(pt6, vect);
    float num7 = dotProduct(pt7, vect);
    float num8 = dotProduct(pt8, vect);
#pragma endregion

#pragma region MIN
    float min1 = getMin(num, num1);
    float min2 = getMin(num1, num2);
    float min3 = getMin(num2, num3);
    float min4 = getMin(num3, num4);

    float min5 = getMin(num4, num5);
    float min6 = getMin(num5, num6);
    float min7 = getMin(num6, num7);
    float min8 = getMin(num7, num8);
    float min8 = getMin(num8, num);

    //float minR = getMin(min, min1);
    //float minR = getMin(min1, min8); ?

#pragma endregion

#pragma region MAX
    float min1 = getMax(num, num1);
    float min2 = getMax(num1, num2);
    float min3 = getMax(num2, num3);
    float min4 = getMax(num3, num4);

    float min5 = getMax(num4, num5);
    float min6 = getMax(num5, num6);
    float min7 = getMax(num6, num7);
    float min8 = getMax(num7, num8);
    float min8 = getMax(num8, num);

    //float maxR = getMax(min, min1);
    //float maxR = getMax(min1, min8); ?

#pragma endregion

    Range rng = { minR, maxR };

    return rng;
}*/