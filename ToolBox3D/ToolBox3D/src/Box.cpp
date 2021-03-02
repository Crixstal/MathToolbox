#include "Box.h"

Box::Box(const Vector3& c, const Vector3& s, const Quaternion& q)
{
	center = c;
	size = s;
	quaternion = q;
}

void Box::myDrawBox(const Vector3& center, const Vector3& size, Color color)
{/*
	Vector3 i = Vector3RotateByQuaternion({1, 0, 0}, q);
	Vector3 j = Vector3RotateByQuaternion({0, 1, 0}, q);
	Vector3 k = Vector3RotateByQuaternion({0, 0, 1}, q);

	Quaternion qA = QuaternionFromAxisAngle({1, 0, 0}, PI / 2);
	Quaternion qB = QuaternionFromAxisAngle({0, 0, 1}, PI / 2);

	rlPushMatrix();
	rlTranslatef(center.x, center.y, center.z);

	Quad quad;
	quad.myDrawQuad(i * size.x, size, qB, color); // right
	quad.myDrawQuad(-i * size.x, size, qB, color); // left

	quad.myDrawQuad(j * size.y, size, q, color); // up
	quad.myDrawQuad(-j * size.y, size, q, color); // down

	quad.myDrawQuad(k * size.z, size, qA, color); // front
	quad.myDrawQuad(-k * size.z, size, qA, color); // back


	rlPopMatrix();*/
}
/*
bool Box::Segment_Box(const Segment& segment, const Box& box, Vector3& interPt, Vector3& interNormal)
{

}*/

void Box::myDrawRoundBox(const Vector3& center, const Vector3& size, Color color)
{

}
