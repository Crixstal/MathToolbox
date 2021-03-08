#include "Box.h"

Box::Box(const Vector3& c, const Vector3& s, const Quaternion& q)
{
	center = c;
	size = s;
	quaternion = q;
}

void Box::myDrawBox(const Color& color)
{
	Vector3 i = Vector3RotateByQuaternion({1, 0, 0}, quaternion);
	Vector3 j = Vector3RotateByQuaternion({0, 1, 0}, quaternion);
	Vector3 k = Vector3RotateByQuaternion({0, 0, 1}, quaternion);

	Quaternion qA = QuaternionFromAxisAngle({1, 0, 0}, PI / 2);
	Quaternion qB = QuaternionFromAxisAngle({0, 0, 1}, PI / 2);

	rlPushMatrix();
	rlTranslatef(center.x, center.y, center.z);

	Quad quad1 (i * size.x, qB, { size.x, size.y });
	Quad quad2 (-i * size.x, qB, { size.x, size.y });
	Quad quad3 (j * size.y, quaternion, { size.x, size.y });
	Quad quad4 (-j * size.y, quaternion, { size.x, size.y });
	Quad quad5 (k * size.z, qA, { size.x, size.y });
	Quad quad6 (-k * size.z, qA, { size.x, size.y });

	quad1.myDrawQuad(color);
	quad2.myDrawQuad(color);
	quad3.myDrawQuad(color);
	quad4.myDrawQuad(color);
	quad5.myDrawQuad(color);
	quad6.myDrawQuad(color);

	rlPopMatrix();
}

bool Box::Segment_Box(const Segment& segment, Vector3& interPt, Vector3& interNormal)
{
	Vector3 i = Vector3RotateByQuaternion({ 1.0f, 0.0f, 0.0f }, quaternion);
	Vector3 j = Vector3RotateByQuaternion({ 0.0f, 1.0f, 0.0f }, quaternion);
	Vector3 k = Vector3RotateByQuaternion({ 0.0f, 0.0f, 1.0f }, quaternion);

	Quad quad({ center + i * size.x }, QuaternionMultiply(quaternion, QuaternionFromAxisAngle({ 0.0f, 0.0f, 1.0f }, PI / 2.0f)), { size.y, size.z });

	if (quad.Segment_Quad(segment, interPt, interNormal))
		return true;

	quad.center = center - i * size.x;
	if (quad.Segment_Quad(segment, interPt, interNormal))
		return true;

	quad.center = center + j * size.y;
	quad.extension = { size.x, size.z };
	quad.quaternion = QuaternionMultiply(quaternion, QuaternionFromAxisAngle({ 0.0f, 1.0f, 0.0f }, PI));
	if (quad.Segment_Quad(segment, interPt, interNormal))
		return true;

	quad.center = center - j * size.y;
	if (quad.Segment_Quad(segment, interPt, interNormal))
		return true;

	quad.center = center + k * size.z;
	quad.extension = { size.x, size.y };
	quad.quaternion = QuaternionMultiply(quaternion, QuaternionFromAxisAngle({ 1.0f, 0.0f, 0.0f }, PI / 2.0f));
	if (quad.Segment_Quad(segment, interPt, interNormal))
		return true;

	quad.center = center - k * size.z;
	if (quad.Segment_Quad(segment, interPt, interNormal))
		return true;

	return false;
}

void Box::drawIntersection(const Segment& segment, Vector3& interPt, Vector3& interNormal, Color color)
{
	Vector3 normal = normalize(Vector3RotateByQuaternion({ 0.0f, 1.0f, 0.0f }, quaternion));

	if (Segment_Box(segment, interPt, interNormal))
	{
		color = RED;
		DrawSphere(interPt, 0.08f, BROWN);
		DrawLine3D(interPt, interNormal + interPt, PURPLE);
	}

	DrawLine3D(segment.ptA, segment.ptB, color);
	myDrawBox(color);
	DrawLine3D(center, 2.0f * normal + center, PURPLE);
}