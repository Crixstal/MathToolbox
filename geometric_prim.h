#pragma once

typedef struct vector2
{
    float x;
    float y;
} vector2;

typedef struct line
{
    float pt;
    vector2 unitpt;
} line;

typedef struct segment
{
    float pt1;
    float pt2;
} segment;

typedef struct circle
{
    float center;
    float radius;
} circle;

typedef struct rect
{
    float center;
    float halfHeight ;
    float halfWidth ;
} rect;

typedef struct orientedRect
{
    float center;
    float halfHeight;
    float halfWidth;
    float angle;
} orientedRect;

typedef struct convexPolygon
{   
    vector2 ;
    float pt;

} convexPolygon;

typedef struct referential2
{
    vector2 origin;
    vector2 i;
    vector2 j;
    float angle;
} referential2;