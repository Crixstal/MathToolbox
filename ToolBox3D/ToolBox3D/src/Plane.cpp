#include "Plane.h"

Plane::Plane(const Vector3& n, const float& d)
{
	normal = normalize(n);
	distance = d;
}

Plane::Plane(const Vector3& n, const Vector3& pos)
{
	normal = normalize(n);
	distance = dotProduct(pos, n);
}

Plane::Plane(const Vector3& vecA, const Vector3& vecB, const Vector3& vecC)
{
	Vector3 AB = vecFromPt(vecA, vecB);
	Vector3 AC = vecFromPt(vecA, vecC);

	normal = normalize(vectorProduct(AB, AC));
	distance = dotProduct(vecA, normal);
}

void Plane::myDrawPlane(Plane& plane, const Color& color)
{
	rlPushMatrix();

	Vector3 center = plane.normal * distance;
	rlTranslatef(center.x, center.y, center.z);

	Vector3 vect;
	float angle;
	QuaternionToAxisAngle(QuaternionFromVector3ToVector3({ 0.f, 1.f, 0.f }, plane.normal), &vect, &angle);

	rlRotatef(vect.x, vect.y, vect.z, angle * RAD2DEG);
	rlScalef(1.0f, 1.0f, 1.0f);

	rlBegin(RL_TRIANGLES);
	rlColor4ub(color.r, color.g, color.b, color.a);

	rlVertex3f(-1, 0, -1);
	rlVertex3f(-1, 0, 1);
	rlVertex3f(1, 0, 1);

	rlVertex3f(-1, 0, -1);
	rlVertex3f(1, 0, 1);
	rlVertex3f(1, 0, -1);

	rlEnd();
	rlPopMatrix();
}

bool Plane::Segment_Plane(const Segment& segment, Plane& plane, Vector3& interPt, Vector3& interNormal)
{
	Vector3 AB = vecFromPt(segment.ptA, segment.ptB);
	float dotAB_normal = dotProduct(AB, plane.normal);

	if (dotAB_normal <= 1e-6)
		return false;
	
	float T = (plane.distance - dotProduct(segment.ptA, plane.normal)) / dotAB_normal;

	//if (plane.distance <= 1e-6)
	//	T = -T;

	if (T <= 1e-6 || T >= 1)
		return false;

	interPt = segment.ptA + AB * T;
	interNormal = plane.normal;

	//if (dotAB_normal <= 1e-6)
	//	interNormal = -interNormal;

	return true;
}

void Plane::drawIntersection(const Segment& segment, Plane& plane, Vector3& interPt, Vector3& interNormal, const Color& color)
{
	if (Segment_Plane(segment, plane, interPt, interNormal))
	{
		DrawLine3D(segment.ptA, segment.ptB, RED);
		myDrawPlane(plane, RED);
	}

	else
	{
		DrawLine3D(segment.ptA, segment.ptB, color);
		myDrawPlane(plane);
	}
}