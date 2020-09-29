#include <stdbool.h>
#include <stdio.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include "geometric_prim.h"

vector2* zeroVector(void)
{
    vector2* vector = {0};

    return vector;
}

float vectorMagnitude(vector2* vector) // vector's "norme"
{
    float vectMag = sqrtf(powf(vector->x, 2) + powf(vector->y, 2));

    return vectMag;
}

vector2* unitVector(vector2* vector)
{
    vector2* vectUnit;
    float vectMag = vectorMagnitude(vector);

    if (vectMag == 0)
        return NULL;

    vectUnit->x = vector->x / vectMag;
    vectUnit->y = vector->y / vectMag;

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

float angle(vector2* vectorA, vector2* vectorB) // angle between 2 vectors
{
    float angle = acosf(dotProduct(vectorA, vectorB) / (vectorMagnitude(vectorA) * vectorMagnitude(vectorB)));

    return angle;
}

void* vect_rotate(vector2* vector)
{
    float angle;
    float x = vector->x;
    float y = vector->y;

    vector->x = x * cosf(angle) - y * sinf(angle);
    vector->y = x * sinf(angle) + y * cosf(angle);
}

void* pt_rotate(vector2* origin, vector2* vector)
{
    float angle;
    float x = vector->x;
    float y = vector->y;
    vector2* vector1;
    /*
    float r = sqrtf(powf(vector->x, 2) + powf(vector->y, 2));

    vector1->x = r * cosf(angle);
    vector1->y = r * sinf(angle);
    */
    vector1->x = origin->x * (x * cosf(angle) - y * sinf(angle));
    vector1->y = origin->y * (x * sinf(angle) + y * cosf(angle));
}

void* right_angle_rotation(vector2* vector)
{
    float angle = M_PI / 2.f;
    float x = vector->x;
    float y = vector->y;    

    vector->x = - y;
    vector->y = x; 
}

vector2* normalVector(vector2* vector)
{
    vector2* vector1 = right_angle_rotation(vector);

    return vector1;
}