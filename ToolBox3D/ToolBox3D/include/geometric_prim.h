#pragma once

#include <cstdio>

#define _USE_MATH_DEFINES
#include <cmath>

#define E 1.401298E-45

#pragma region GEOMETRICAL STRUCTURES
struct point3
{
    float x;
    float y;
    float z;
};

struct vector3
{
    float x; 
    float y;
    float z;
};

struct sphere
{
    point3 center;
    float radius;
};

struct plane
{
    vector3 normal;
    float d;
};
#pragma endregion

bool Segment_Plane(vector3 ptA, vector3 ptB, plane plane, vector3& interPt, vector3& internormal);
bool Segment_Capsule();
bool Segment_Box();
bool Segment_RoundBox();
bool Segment_Cylindre();