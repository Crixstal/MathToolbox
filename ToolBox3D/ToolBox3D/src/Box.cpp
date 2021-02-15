#include "Box.h"

void Box::myDrawBox(const Vector3& center, const Vector3& extensions, const Color& color)
{
	Vector3 i = Vector3RotateByQuaternion({1, 0, 0}, q);
	Vector3 j = Vector3RotateByQuaternion({0, 1, 0}, q);
	Vector3 k = Vector3RotateByQuaternion({0, 0, 1}, q);

	Quaternion qA = QuaternionFromAxisAngle({1, 0, 0}, PI / 2);
	Quaternion qB = QuaternionFromAxisAngle({0, 0, 1}, PI / 2);

	rlPushMatrix();
	rlTranslatef(center.x, center.y, center.z);

	Quad quad;
	quad.myDrawQuad(i * extensions.x, extensions, qB, color); // right
	quad.myDrawQuad(-i * extensions.x, extensions, qB, color); // left

	quad.myDrawQuad(j * extensions.y, extensions, q, color); // up
	quad.myDrawQuad(-j * extensions.y, extensions, q, color); // down

	quad.myDrawQuad(k * extensions.z, extensions, qA, color); // front
	quad.myDrawQuad(-k * extensions.z, extensions, qA, color); // back


	rlPopMatrix();
}
/*
bool Box::Segment_Box(const Segment& segment, Box box, Vector3& interPt, Vector3& interNormal)
{

}*/

void Box::myDrawRoundBox(const Vector3& center, const Vector3& extensions, const Color& color)
{

}
