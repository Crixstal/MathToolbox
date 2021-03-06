#include "geometric_prim.h"

float getMin(float a, float b)
{
    if (a < b)
        return a;
    else
        return b;
}

float getMax(float a, float b)
{
    if (a > b)
        return a;
    else
        return b;
}

range globalRange(range rng1, range rng2)
{
    range globalRng;

    globalRng.min = getMin(rng1.min, rng2.min);
    globalRng.max = getMax(rng1.max, rng2.max);

    return globalRng;
}

range globRngVal(range rng, float a)
{
    range globRngVal;

    globRngVal.min = getMin(rng.min, a);
    globRngVal.max = getMax(rng.max, a);

    return globRngVal;
}

bool rangeOverlap(range rng1, range rng2)
{
    if (rng1.min > rng2.max || rng2.min > rng1.max)
        return false;

    return true;
}

range ptOnAxisRng(point2 pt, vector2 vect)
{
    vector2 vectPt = { pt.x, pt.y };
    float num = dotProduct(vectPt, vect);
    range rng = { num, num };

    return rng;
}

range segOnAxisRng(segment seg, vector2 vect)
{
    float min, max;
    vector2 vectPt1 = { seg.pt1.x, seg.pt1.y };
    float num1 = dotProduct(vectPt1, vect);
    vector2 vectPt2 = { seg.pt2.x, seg.pt2.y };
    float num2 = dotProduct(vectPt2, vect);

    if (num1 <= num2)
    {
        min = num1;
        max = num2;
    }
    else
    {
        min = num2;
        max = num1;
    }

    range rng = { min, max };

    return rng;
}

range boxOnAxisRng(rect box, vector2 vect)
{
    point2 pt = { box.center.x + box.halfWidth, box.center.y + box.halfHeight };
    point2 pt1 = { box.center.x - box.halfWidth, box.center.y + box.halfHeight };
    point2 pt2 = { box.center.x - box.halfWidth, box.center.y - box.halfHeight };
    point2 pt3 = { box.center.x + box.halfWidth, box.center.y - box.halfHeight };

    vector2 vect1 = { pt.x, pt.y };
    vector2 vect2 = { pt1.x, pt1.y };
    vector2 vect3 = { pt2.x, pt2.y };
    vector2 vect4 = { pt3.x, pt3.y };

    float num = dotProduct(vect, vect);
    float num1 = dotProduct(vect1, vect);
    float num2 = dotProduct(vect2, vect);
    float num3 = dotProduct(vect3, vect);

    float min = getMin(num, num1);
    float min1 = getMin(num2, num3);
    float minR = getMin(min, min1);

    float max = getMax(num, num1);
    float max1 = getMax(num2, num3);
    float maxR = getMax(max, max1);

    range rng = { minR, maxR };

    return rng;
}
/*
range circleOnAxisRng(vector2 vect)
{
    range rng;



    return rng;
}*/