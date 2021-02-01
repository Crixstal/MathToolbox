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
	Vector3 AB = vecB - vecA;
	Vector3 AC = vecC - vecA;

	normal = normalize(vectorProduct(AB, AC));
	direction = dotProduct(vecA, normal);
}

bool Plane::Segment_Plane(const Vector3& vecA, const Vector3& vecB, Plane plane, Vector3& interPt, Vector3& interNormal)
{
	Vector3 AB = vecB - vecA;

	if (dotProduct(AB, plane.normal) < 1e-6)
		return false;

	Vector3 vector = plane.normal * plane.direction - vecA;

	float T = 2 * dotProduct(vector, plane.normal) / dotProduct(AB, plane.normal);

	if (plane.direction < 1e-6)
		T = -T;

	interPt = vecA + AB * T;
	interNormal = plane.normal;

	return true;
}
/*
void Plane::drawPlane(Vector3 normal)
{
	DrawPlane(normal, { 3, 3 }, GREEN);

	if (Segment_Plane() == true)
		DrawLine3D({ 0, 0, 0 }, { 2, 3, 1 }, RED);
	else
		DrawLine3D({ 0, 0, 0 }, { 2, 3, 1 }, GREEN);
}
*/