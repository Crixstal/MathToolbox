#include <stdbool.h>
#include <stdio.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include "geometric_prim.h"

vector2 zeroVector()
{
    vector2 vector = {0, 0};

    return vector;
}

float vectorMagnitude(vector2 vector) // vector's "norme"
{
    float vectMag = sqrtf(powf(vector.x, 2) + powf(vector.y, 2));

    return vectMag;
}

vector2 unitVector(vector2 vector)
{
    vector2 vectUnit;
    float vectMag = vectorMagnitude(vector);

    if (vectMag == 0)
        return vector;

    vectUnit.x = vector.x / vectMag;
    vectUnit.y = vector.y / vectMag;

    return vectUnit;
}

bool compareVector(vector2 vectorA, vector2 vectorB) // 0 false, 1 true
{
    return (fabs(vectorA.x - vectorB.x) <= E) && (fabs(vectorA.y - vectorB.y) <= E);
}

float squareMagnitude(vector2 vector)
{
    float squareMag = powf(vector.x, 2) + powf(vector.y, 2);

    return squareMag;
}

float distance(point2 pointA, point2 pointB) // between 2 pts
{
    float dist = sqrtf(powf(pointB.x - pointA.x, 2) + powf(pointB.y - pointA.y, 2));

    return dist;
}

vector2 addition(vector2 vectorA, vector2 vectorB)
{
    vector2 add;

    add.x = vectorA.x + vectorB.x;
    add.y = vectorA.y + vectorB.y;

    return add;
}

vector2 subtraction(vector2 vectorA, vector2 vectorB)
{
    vector2 sub;

    sub.x = vectorA.x - vectorB.x;
    sub.y = vectorA.y - vectorB.y;

    return sub;
}

vector2 scale(vector2 vector, float k) // multiplication vector/scalar
{
    vector2 scale;

    scale.x = k * vector.x;
    scale.y = k * vector.y;

    return scale;
}

vector2 negate(vector2 vector) // opposite vector
{
    vector2 neg;

    neg.x = -1 * vector.x;
    neg.y = -1 * vector.y;

    return neg;
}

float dotProduct(vector2 vectorA, vector2 vectorB)
{
    float dot = (vectorA.x * vectorB.x) + (vectorA.y * vectorB.y);

    return dot;
}

float angle(vector2 vectorA, vector2 vectorB) // angle between 2 vectors
{
    float vectMagA = vectorMagnitude(vectorA);
    float vectMagB = vectorMagnitude(vectorB);

    if (vectMagA == 0 || vectMagB == 0)
        return 0;

    float angle = acosf(dotProduct(vectorA, vectorB) / (vectMagA * vectMagB));

    return angle * (180/M_PI); // in degree
}

vector2 vectRotate(vector2 vector, float angle) // angle in radian
{
    float x = vector.x;

    if (vector.x == 0 && vector.y == 0)
    {
        vector.x = sinf(angle);
	    vector.y = cosf(angle);
    }

    else
    {
        vector.x = x * cosf(angle) - vector.y * sinf(angle);
        vector.y = x * sinf(angle) + vector.y * cosf(angle);
    }
    
    return vector;
}

point2 ptRotate(point2 origin, point2 point, float angle) // angle in radian
{
    if (point.x == origin.x && point.y == origin.y)
        return point;

    float x = point.x;
    
    point.x = x * cosf(angle) - point.y * sinf(angle);
    point.y = x * sinf(angle) + point.y * cosf(angle);

    return point;
}

vector2 rightAngleRotation(vector2 vector)
{ 
    float x = vector.x;

    vector.x = - vector.y;
    vector.y = x; 

    return vector;
}

vector2 normalVector(vector2 vector)
{
    vector2 rotVect = rightAngleRotation(vector);

    return rotVect;
}