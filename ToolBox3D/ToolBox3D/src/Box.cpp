#include "Box.h"

Box::Box(const Vector3& c, const Vector3& s, const Quaternion& q)
{
	center = c;
	size = s;
	quaternion = q;
}

void Box::myDrawBox(const Box& box, Color color)
{
	Vector3 i = Vector3RotateByQuaternion({1, 0, 0}, box.quaternion);
	Vector3 j = Vector3RotateByQuaternion({0, 1, 0}, box.quaternion);
	Vector3 k = Vector3RotateByQuaternion({0, 0, 1}, box.quaternion);

	Quaternion qA = QuaternionFromAxisAngle({1, 0, 0}, PI / 2);
	Quaternion qB = QuaternionFromAxisAngle({0, 0, 1}, PI / 2);

	rlPushMatrix();
	rlTranslatef(box.center.x, box.center.y, box.center.z);

	Quad quad1 (i * box.size.x, qB, { box.size.x, box.size.y });
	Quad quad2 (-i * box.size.x, qB, { box.size.x, box.size.y });
	Quad quad3 (j * box.size.y, box.quaternion, { box.size.x, box.size.y });
	Quad quad4 (-j * box.size.y, box.quaternion, { box.size.x, box.size.y });
	Quad quad5 (k * box.size.z, qA, { box.size.x, box.size.y });
	Quad quad6 (-k * box.size.z, qA, { box.size.x, box.size.y });

	quad1.myDrawQuad(quad1, color); // right
	quad2.myDrawQuad(quad2, color); // left
	quad3.myDrawQuad(quad3, color); // up
	quad4.myDrawQuad(quad4, color); // down
	quad5.myDrawQuad(quad5, color); // front
	quad6.myDrawQuad(quad6, color); // back

	rlPopMatrix();
}

bool Box::Segment_Box(const Segment& segment, Vector3& interPt, Vector3& interNormal)
{
	Vector3 i = Vector3RotateByQuaternion({ 1, 0, 0 }, quaternion);
	Vector3 j = Vector3RotateByQuaternion({ 0, 1, 0 }, quaternion);
	Vector3 k = Vector3RotateByQuaternion({ 0, 0, 1 }, quaternion);

	Quaternion qA = QuaternionFromAxisAngle({ 1, 0, 0 }, PI / 2);
	Quaternion qB = QuaternionFromAxisAngle({ 0, 0, 1 }, PI / 2);

	Quad quad;

	quad.center = center + i * size.x;
	quad.extension = { size.y, size.z };
	quad.quaternion = QuaternionMultiply(quaternion, QuaternionFromAxisAngle({ 0.0f, 0.0f, 1.0f }, PI / 2.0f));
	if (Segment_Quad(segment, quad, interPt, interNormal))
		return true;

	quad.center = center - i * size.x;
	if (Segment_Quad(segment, quad, interPt, interNormal))
		return true;

	quad.center = center + j * size.y;
	quad.extension = { size.x, size.z };
	quad.quaternion = QuaternionMultiply(quaternion, QuaternionFromAxisAngle({ 0.0f, 1.0f, 0.0f }, PI));
	if (Segment_Quad(segment, quad, interPt, interNormal))
		return true;

	quad.center = center - j * size.y;
	if (Segment_Quad(segment, quad, interPt, interNormal))
		return true;

	quad.center = center + k * size.z;
	quad.extension = { size.x, size.y };
	quad.quaternion = QuaternionMultiply(quaternion, QuaternionFromAxisAngle({ 1.0f, 0.0f, 0.0f }, PI / 2.0f));
	if (Segment_Quad(segment, quad, interPt, interNormal))
		return true;

	quad.center = center - k * size.z;
	if (Segment_Quad(segment, quad, interPt, interNormal))
		return true;
}

void Box::drawIntersection(const Segment& segment, const Box& box, Vector3& interPt, Vector3& interNormal, Color color)
{
	Vector3 normal = normalize(Vector3RotateByQuaternion({ 0.0f, 1.0f, 0.0f }, box.quaternion));

	if (Segment_Box(segment, interPt, interNormal))
	{
		color = RED;
		DrawSphere(interPt, 0.08f, BROWN);
		DrawLine3D(interPt, interNormal + interPt, PURPLE);
	}

	DrawLine3D(segment.ptA, segment.ptB, color);
	myDrawBox(box, color);
	DrawLine3D(box.center, normal + box.center, PURPLE);
}