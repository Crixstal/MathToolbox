#include <math.h>
#include <stdbool.h>

#include "geometric_prim.h"

vector2* zeroVector(void)
{
    vector2 vector = {0, 0};

    return &vector;
}

vector2* unitVector(vector2* vector)
{
    vector2* vectUnit;

    if (vectorMagnitude(vector) == 0)
        return NULL;

    vectUnit->x = vector->x / vectorMagnitude(vector);
    vectUnit->y = vector->y / vectorMagnitude(vector);

    return vectUnit;
}

bool compareVector(vector2* vectorA, vector2* vectorB)
{
    bool equal;
    const int e = 1.401298E-45;

    if (vectorA->x > vectorB->x - e && vectorA->x < vectorB->x + e)
    {
        if (vectorA->y > vectorB->y - e && vectorA->y < vectorB->y + e)
            equal = true;
        else
            equal = false;
    }
    else
        equal = false;

    return equal;
}

float vectorMagnitude(vector2* vector) // vector's "norme"
{
    float vectMag = sqrtf(powf(vector->x, 2) + powf(vector->y, 2));

    return vectMag;
}

float squareMagnitude(vector2* vector)
{
    float squareMag = sqrtf(powf(vector->x, 2) + powf(vector->y, 2)) * sqrtf(powf(vector->x, 2) + powf(vector->y, 2));

    return squareMag;
}

float distance(vector2* vectorA, vector2* vectorB) // between 2 pts
{
    float dist = sqrtf(powf(vectorB->x - vectorA->x, 2) + powf(vectorB->y - vectorA->y, 2));

    return dist;
}

vector2* addition(vector2* vectorA, vector2* vectorB)
{
    vector2* add;

    add->x = vectorA->x + vectorB->x;
    add->y = vectorA->y + vectorB->y;

    return add;
}

vector2* subtraction(vector2* vectorA, vector2* vectorB)
{
    vector2* sub;

    sub->x = vectorA->x - vectorB->x;
    sub->y = vectorA->y - vectorB->y;

    return sub;
}

vector2* scale(vector2* vector, float k) // multiplication vector/scalar
{
    vector2* scale;

    scale->x = k * vector->x;
    scale->y = k * vector->y;

    return scale;
}

vector2* negate(vector2* vector) // opposite vector
{
    vector2* neg;

    neg->x = -1 * vector->x;
    neg->y = -1 * vector->y;

    return neg;
}

float dotProduct(vector2* vectorA, vector2* vectorB)
{
    float dot = (vectorA->x * vectorB->x) + (vectorA->y * vectorB->y);

    return dot;
}

float angle(vector2* vectorA, vector2* vectorB)
{
    float angle = acosf(dotProduct(vectorA, vectorB) / (vectorMagnitude(vectorA) * vectorMagnitude(vectorB)));

    return angle;
}