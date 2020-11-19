#include <stdbool.h>
#include <math.h>

#include "geometric_prim.h"

bool Point_Point(point2 pt1, point2 pt2, float e)
{
    return (fabs(pt1.x - pt2.x) <= E && fabs(pt1.y - pt2.y) <= E);
}

bool Point_Line(point2 pt, line line, float e)
{
    vector2 normal = normalVector(line.vectDir);
    vector2 baseToPt = {pt.x - line.base.x, pt.y - line.base.y};

    return (fabs(dotProduct(baseToPt, normal)) <= E);
}

bool Point_Segment(point2 pt, segment seg) // check
{
    line segLine = {pt, {seg.pt2.x - seg.pt1.x, seg.pt2.y - seg.pt1.y}};

    return (Point_Line(pt, segLine, E) == 0);
}

bool Point_Circle(point2 pt, circle circle)
{
    vector2 vect = {pt.x - circle.center.x, pt.y - circle.center.y};

    return (squareMagnitude(vect) <= circle.radius * circle.radius);
}

bool Point_Box(point2 pt, rect box)
{
    return (pt.x <= box.center.x + box.halfWidth && pt.x >= box.center.x - box.halfWidth
             && pt.y <= box.center.y + box.halfHeight && pt.y >= box.center.y - box.halfHeight);
}

bool Line_Line(line line1, line line2) // not finished
{
    vector2 n2 = {-line2.vectDir.y, line2.vectDir.x};

    if (dotProduct(n2, line1.vectDir) != 0)
        return true;
    else // check if // or coincide
        return false;  
}

bool Line_Segment(line line1, segment seg)
{   
    vector2 vectAP1 = {seg.pt1.x - line1.base.x, seg.pt1.y - line1.base.y};
    vector2 vectAP2 = {seg.pt2.x - line1.base.x, seg.pt2.y - line1.base.y};
    vector2 vectN = {line1.vectDir.y, line1.vectDir.x};

    if (dotProduct(vectAP1, vectN) * dotProduct(vectAP2, vectN) > 0)
        return true;
    else
    {
        line line2 = {seg.pt1, {seg.pt2.x - seg.pt1.x, seg.pt2.y - seg.pt1.y}};
        return Line_Line(line1, line2);
    }
}

bool Line_Circle(line line1, circle circle)
{
    return Point_Line(circle.center, line1, circle.radius * circle.radius);
}
/*
bool Segment_Segment(segment seg1, segment seg2)
{
    range rg1;
    range rg2;

    vector2 vectorDir;
    vector2 OA;
    vector2 OB;

    rg1.min = getMin(dotProduct(OA, vectorDir), dotProduct(OB, vectorDir));
    rg2.max = getMax(dotProduct(OA, vectorDir), dotProduct(OB, vectorDir));

    if (rg1.min > rg2.max || rg2.min > rg1.max) //dissociate range
        return true;

    return false;
}
*/
bool Segment_Circle(segment seg, circle circle)
{
    vector2 segVect = { seg.pt2.x - seg.pt1.x, seg.pt2.y - seg.pt1.y };
    line segLine = { seg.pt1, segVect };
    rightAngleRotation(segVect);

    range circleRange = circleRng(circle, segVect);
    range segRange = segmentRng(seg, segVect);

    if (Point_Line(circle.center, segLine, circle.radius) == 0)
        return 0;
    else if (Point_Circle(seg.pt1, circle) == 1 || Point_Circle(seg.pt2, circle) == 1)
        return 1;
    else
        return (rangeOverlap(circleRange, segRange));
}

bool Circle_Circle(circle circle1, circle circle2)
{
    float centers_distance = distance(circle1.center, circle2.center);
    return centers_distance <= circle1.radius + circle2.radius;
}

bool Circle_Box(circle circle, rect box)
{
    return (fabs(circle.center.x - box.center.x) <= box.halfWidth && fabs(circle.center.y - box.center.y) <= box.halfHeight);
}

bool Box_Box(rect box1, rect box2)
{
    return (box1.center.y - box1.halfHeight > box2.center.y + box2.halfHeight || box1.center.y + box1.halfHeight < box2.center.y - box2.halfHeight ||
            box1.center.x + box1.halfWidth < box2.center.x - box2.halfWidth || box1.center.x - box1.halfWidth > box2.center.x + box2.halfWidth);
}
/*
bool ConvexPolygon_Point(convexPolygon poly, point2 pt)
{
    for (int i = 1; i < poly.sizeArray; i++)
    {
        vector2 vect = {poly.array_points[i].x - poly.array_points[i - 1].x, poly.array_points[i].y - poly.array_points[i - 1].y};
        
        range polyRng = convexRng(poly, vect);
        range ptRng = pointRng(pt, vect);

        return (rangeOverlap(polyRng, ptRng));
    }
}

bool ConvexPolygon_ConvexPolygon(convexPolygon poly1, convexPolygon poly2)
{

}

bool ConvexPolygon_Circle(convexPolygon poly, circle circle)
{
    
}*/