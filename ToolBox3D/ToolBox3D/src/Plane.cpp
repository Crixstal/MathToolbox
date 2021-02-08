#include "Plane.h"

Plane::Plane(Vector3 n, float d)
{
	normal = n;
	direction = d;
}

Plane::Plane(Vector3 n, Vector3 pos)
{
	normal = n;
	direction = dotProduct(pos, n);
}

Plane::Plane(Vector3 vecA, Vector3 vecB, Vector3 vecC)
{
	Vector3 AB = vecFromPt(vecA, vecB);
	Vector3 AC = vecFromPt(vecA, vecC);

	normal = normalize(vectorProduct(AB, AC));
	direction = dotProduct(vecA, normal);
}

bool Plane::Segment_Plane(const Segment& segment, Plane plane, Vector3& interPt, Vector3& interNormal)
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

void Plane::myDrawPlane()
{
	rlBegin(RL_QUADS);

	rlColor3f(0.f, 1.f, 0.f);

	rlVertex3f(-1.f, 2.f, 3.f);
	rlVertex3f( 1.f, 2.f, 3.f);
	rlVertex3f( 1.f, 0.f, 0.f);
	rlVertex3f(-1.f, 0.f, 0.f);

	rlEnd();
}
