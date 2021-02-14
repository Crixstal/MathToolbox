#include "Plane.h"

Plane::Plane(const Vector3& n, const float& d)
{
	normal = normalize(n);
	direction = d;
}

Plane::Plane(const Vector3& n, const Vector3& pos)
{
	normal = normalize(n);
	direction = dotProduct(pos, n);
}

Plane::Plane(const Vector3& vecA, const Vector3& vecB, const Vector3& vecC)
{
	Vector3 AB = vecFromPt(vecA, vecB);
	Vector3 AC = vecFromPt(vecA, vecC);

	normal = normalize(vectorProduct(AB, AC));
	direction = dotProduct(vecA, normal);
}

bool Plane::Segment_Plane(const Segment& segment, Plane& plane, Vector3& interPt, Vector3& interNormal)
{
	Vector3 AB = vecFromPt(segment.ptA, segment.ptB);

	if (dotProduct(AB, plane.normal) < 1e-6)
		return false;

	Vector3 vector = plane.normal * plane.direction - segment.ptA;

	float T = 2 * dotProduct(vector, plane.normal) / dotProduct(AB, plane.normal);

	if (plane.direction < 1e-6)
		T = -T;

	interPt = segment.ptA + AB * T;
	interNormal = plane.normal;

	return true;
}

void Plane::myDrawPlane(Plane& plane, const Color& color)
{
	rlPushMatrix();
	//rlTranslatef(centerPos.x, centerPos.y, centerPos.z);
	//rlScalef(size.x, 1.0f, size.y);

	rlBegin(RL_QUADS);
	rlColor4ub(color.r, color.g, color.b, color.a);
	rlNormal3f(plane.normal.x, plane.normal.y, plane.normal.z);

	rlVertex3f(-1.0f, 0.0f, -1.0f);
	rlVertex3f(-1.0f, 0.0f, 1.0f);
	rlVertex3f(1.0f, 3.0f, 1.0f);
	rlVertex3f(1.0f, 3.0f, -1.0f);

	rlEnd();
	rlPopMatrix();
}

void Plane::drawIntersection(const Segment& segment, Plane& plane, Vector3& interPt, Vector3& interNormal)
{
	if (Segment_Plane(segment, plane, interPt, interNormal))
	{
		DrawLine3D(segment.ptA, segment.ptB, RED);
		myDrawPlane(plane, RED);
	}

	else
	{
		DrawLine3D(segment.ptA, segment.ptB, GREEN);
		myDrawPlane(plane, GREEN);
	}
}