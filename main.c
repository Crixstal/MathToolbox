#include <stdio.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include "geometric_prim.h"

void testVectors()
{/*
    vector2 vector = zeroVector;
    printf("zeroVector : x = %f, y = %f\n", vector.x, vector.y);
    point2 point1 = {3.f, 2.f};
    point2 pointO = {10.f, 20.f};

    float angle = M_PI / 2;

    printf("point1 : x = %f, y = %f\n", point1.x, point1.y);
    printf("origin : x = %f, y = %f\n", pointO.x, pointO.y);

    ptRotate(&pointO, &point1, angle);
    
    printf("point after rotate : x = %f, y = %f", point1.x, point1.y);
*/}

void testReferential()
{
    referential2 referential = {{2, 3}, {1, 1}, {-1, 1}};
    point2 pt = {2.f, 2.f};
    vector2 vect = {2.f, 2.f};

    printf("local referential: origin (%f, %f), i (%f, %f), j (%f, %f)\n", referential.origin.x, referential.origin.y, referential.i.x, referential.i.y, referential.j.x, referential.j.y);
    printf("point in local = %f, %f\n", pt.x, pt.y);
    printf("vector in local = %f, %f\n\n", vect.x, vect.y);

    locToGlobPos(referential, &pt);
    printf("point (local->global) = %f, %f\n", pt.x, pt.y);

    globToLocPos(referential, &pt);
    printf("point (global->local) = %f, %f\n\n", pt.x, pt.y);

    locToGlobVect(referential, &vect);
    printf("vect (local->global) = %f, %f\n", vect.x, vect.y);

    globToLocVect(referential, &vect);
    printf("vect (global->local) = %f, %f\n", vect.x, vect.y);
}

int main()
{
    //testVectors();
    testReferential();

    return 0;
}