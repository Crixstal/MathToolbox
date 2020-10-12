#include <stdbool.h>
#include <math.h>

#include "geometric_prim.h"

bool Point_Point(point2 pt1, point2 pt2)
{
    return (fabs(pt1.x - pt2.x) < E && fabs(pt1.y - pt2.y) < E);
}

bool Point_Line(point2 pt, line line)
{
    vector2 normal = normalVector(line.vectDir);
    vector2 bP = {pt.x - line.base.x, pt.y - line.base.y};

    return (fabs(dotProduct(bP, normal)) < E);
}

bool Point_Segment(point2 pt, segment seg) // check
{
    line segLine = {pt, {seg.pt2.x - seg.pt1.x, seg.pt2.y - seg.pt1.y}};

    return (Point_Line(pt, segLine) == 0);
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

bool Line_Line(line line1, line line2)
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

}

bool Segment_Segment(segment seg1, segment seg2)
{

}

bool Segment_Circle(segment seg, circle circle)
{

}

bool Circle_Circle(circle circle1, circle circle2)
{

}

bool Circle_Box(circle circle, rect box)
{

}

bool Box_Box(rect box1, rect box2)
{

}

bool ConvexPolygon_Point(point2 pt, convexPolygon poly)
{

}

bool ConvexPolygon_ConvexPolygon(convexPolygon poly1, convexPolygon poly2)
{

}

bool ConvexPolygon_Circle(convexPolygon poly, circle circle)
{
    
}
