#pragma once

#include <stdbool.h>

// GEOMETRICAL STRUCTURES
typedef struct point2
{
    float x;
    float y;
} point2;

typedef struct vector2
{
    float x;
    float y;
} vector2;

typedef struct line
{
    point2 base;
    vector2 vectDir;
} line;

typedef struct segment
{
    point2 pt1;
    point2 pt2;
} segment;

typedef struct circle
{
    point2 center;
    float radius;
} circle;

typedef struct rect
{
    point2 center;
    float halfHeight;
    float halfWidth;
} rect;

typedef struct orientedRect
{
    rect rect;
    float angle;
} orientedRect;

typedef struct convexPolygon
{   
    point2* array_points;
} convexPolygon;

typedef struct referential2
{
    point2 origin;
    vector2 i;
    vector2 j;
    float angle;
} referential2;

typedef struct range
{
    float min;
    float max;
} range;

// VECTORS
vector2 zeroVector();
float vectorMagnitude(vector2 vector);
vector2 unitVector(vector2 vector);
bool compareVector(vector2 vectorA, vector2 vectorB);
float squareMagnitude(vector2 vector);
float distance(point2 pointA, point2 pointB);

// OPERATIONS ON VECTOR
vector2 addition(vector2 vectorA, vector2 vectorB);
vector2 subtraction(vector2 vectorA, vector2 vectorB);
vector2 scale(vector2 vector, float k);
vector2 negate(vector2 vector);
float dotProduct(vector2 vectorA, vector2 vectorB);

// VECTORS AND ANGlE
float angle(vector2 vectorA, vector2 vectorB);
void vectRotate(vector2 vector, float angle);
void ptRotate(point2 origin, point2 point, float angle);
void rightAngleRotation(vector2 vector);
vector2 normalVector(vector2 vector);

// CHANGE OF REFERENTIAL
void locToGlobPos(referential2 local, point2* pt);
void globToLocPos(referential2 local, point2* pt);
void locToGlobVect(referential2 local, vector2* vect);
void globToLocVect(referential2 local, vector2* vect);

// RANGE
float getMin(float a, float b);
float getMax(float a, float b);
range globalRange(range rng1, range rng2);
range globRngVal(range rng, float a);
bool rangeOverlap(range rng1, range rng2);
range ptOnAxisRng(point2 pt, vector2 vect);
range segOnAxisRng(segment seg, vector2 vect);
range boxOnAxisRng(rect box, vector2 vect);
range circleOnAxisRng(vector2 vect);

// BINARY DETECTION
bool Point_Point(point2 pt1, point2 pt2);
bool Point_Line(point2 pt, line line);
bool Point_Segment(point2 pt, segment seg);
bool Point_Circle(point2 pt, circle circle);
bool Point_Box(point2 pt, rect box);
bool Line_Line(line line1, line line2);
bool Line_Segment(line line1, segment seg);
bool Line_Circle(line line1, circle circle);
bool Segment_Segment(segment seg1, segment seg2);
bool Segment_Circle(segment seg, circle circle);
bool Circle_Circle(circle circle1, circle circle2);
bool Circle_Box(circle circle, rect box);
bool Box_Box(rect box1, rect box2);