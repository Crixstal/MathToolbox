#include <stdio.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include "geometric_prim.h"

void testVectors()
{
    vector2 vector0 = zeroVector();
    printf("zeroVector : x = %f, y = %f\n\n", vector0.x, vector0.y);

    vector2 vect = {2, 4};
    printf("vector : x = %f, y = %f\n\n", vect.x, vect.y);

    float vectMag = vectorMagnitude(vect);
    printf("vector magnitude = %f\n\n", vectMag);

    vector2 vectUnit = unitVector(vect);
    printf("vector unit : x = %f, y = %f\n\n", vectUnit.x, vectUnit.y);

    vector2 vectComp = {2, 4};
    bool equal = compareVector(vect, vectComp);
    printf("u(%f, %f) and v(%f, %f) equal ? -> %d / (0 = false, 1 = true)\n\n", vect.x, vect.y, vectComp.x, vectComp.y, equal);

    float squareMag = squareMagnitude(vect);
    printf("square magnitude = %f\n\n", squareMag);

    point2 A = {2.f, 2.f}, B = {4.f, 4.f};
    float dist = distance(A, B);
    printf("distance = %f\n\n", dist);

    vector2 vectA = {2, 4}, vectB = {7, 9};
    printf("vectA : x = %f, y = %f / vectB : x = %f, y = %f\n\n", vectA.x, vectA.y, vectB.x, vectB.y);

    vector2 add = addition(vectA, vectB);
    printf("addition : x = %f, y = %f\n", add.x, add.y);

    vector2 sub = subtraction(vectA, vectB);
    printf("subtraction : x = %f, y = %f\n", sub.x, sub.y);

    float k = 2;
    vector2 scal = scale(vectA, k);
    printf("scale : x = %f, y = %f\n", scal.x, scal.y);

    vector2 neg = negate(vectA);
    printf("negate : x = %f, y = %f\n\n", neg.x, neg.y);

    float dot = dotProduct(vectA, vectB);
    printf("dot product = %f\n\n", dot);

    float ang = angle(vectA, vectB);
    printf("angle in degree = %f\n\n", ang);

    float n = M_PI / 36; // 5 degree
    vector2 rot = vectRotate(vectA, n);
    printf("vect rotate : x = %f, y = %f\n\n", rot.x, rot.y);

    point2 origin = {0, 0}, point = {3, 2};
    point2 rotPt = ptRotate(origin, point, n);
    printf("point rotate : x = %f, y = %f\n\n", rotPt.x, rotPt.y);
   
    vector2 right = rightAngleRotation(vectA);
    printf("right angle vector : x = %f, y = %f\n\n", right.x, right.y);

    vector2 nor = normalVector(vectA);
    printf("normal vector : x = %f, y = %f\n", nor.x, nor.y);
}

void testReferential()
{
    referential2 referential = {{2, 3}, unitVector((vector2){1, 1}), unitVector((vector2){-1, 1})};
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
    testVectors();
    //testReferential();

    return 0;
}