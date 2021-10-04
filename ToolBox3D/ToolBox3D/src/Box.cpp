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

bool Box::isPointInsideBox(const Vector3& point, const Box& box)
{
	Referential ref (box.center, box.quaternion);

	// Find box referential
	Vector3 centerPoint = point - box.center;

	// Compute dot products between box's center-point vector and box's unit vector
	centerPoint = { dotProduct(centerPoint, ref.i), dotProduct(centerPoint, ref.j), dotProduct(centerPoint, ref.k) };
	// Compare dot with box extensions, since dot products are point projection on xyz plane according to box referential
	return ((centerPoint.x <= box.size.x && centerPoint.x >= -box.size.x)
		&& (centerPoint.y <= box.size.y && centerPoint.y >= -box.size.y)
		&& (centerPoint.z <= box.size.z && centerPoint.z >= -box.size.z));
}

Quad Box::getRight() const
{
	Quaternion qdQuaternion = QuaternionMultiply(quaternion, QuaternionFromAxisAngle({ 0.f, 0.f, 1.f }, -PI / 2));
	Vector3 qdCenter = Vector3RotateByQuaternion((1.f, 0.f, 0.f) * size, quaternion) + center;

	return { qdCenter, qdQuaternion, {size.x, size.z} };
}

Quad Box::getLeft() const
{
	Quaternion qdQuaternion = QuaternionMultiply(quaternion, QuaternionFromAxisAngle({ 0.f, 0.f, 1.f }, PI / 2));
	Vector3 qdCenter = Vector3RotateByQuaternion((-1.f, 0.f, 0.f) * size, quaternion) + center;

	return { qdCenter, qdQuaternion, {size.x, size.z} };
}

Quad Box::getFront() const
{
	Quaternion qdQuaternion = QuaternionMultiply(quaternion, QuaternionFromAxisAngle({ 1.f, 0.f, 0.f }, PI / 2));
	Vector3 qdCenter = Vector3RotateByQuaternion((0.f, 0.f, 1.f) * size, quaternion) + center;

	return { qdCenter, qdQuaternion, {size.x, size.z} };
}

Quad Box::getBack() const
{
	Quaternion qdQuaternion = QuaternionMultiply(quaternion, QuaternionFromAxisAngle({ 1.f, 0.f, 0.f }, -PI / 2));
	Vector3 qdCenter = Vector3RotateByQuaternion((0.f, 0.f, -1.f) * size, quaternion) + center;

	return { qdCenter, qdQuaternion, {size.x, size.z} };
}

Quad Box::getUp() const
{
	Quaternion qdQuaternion = QuaternionMultiply(quaternion, QuaternionFromAxisAngle({ 1.f, 0.f, 0.f }, 0.f));
	Vector3 qdCenter = Vector3RotateByQuaternion((0.f, 1.f, 0.f) * size, quaternion) + center;

	return { qdCenter, qdQuaternion, {size.x, size.z} };
}

Quad Box::getBottom() const
{
	Quaternion qdQuaternion = QuaternionMultiply(quaternion, QuaternionFromAxisAngle({ 1.f, 0.f, 0.f }, PI));
	Vector3 qdCenter = Vector3RotateByQuaternion((0.f, -1.f, 0.f) * size, quaternion) + center;

	return { qdCenter, qdQuaternion, {size.x, size.z} };
}

bool Box::Segment_Box(const Segment& segment, Vector3& interPt, Vector3& interNormal)
{
	if (isPointInsideBox(segment.ptA, *this)) 
		return false;

	Referential boxRef (center, quaternion);
	Vector3 AB = vecFromPt(segment.ptA, segment.ptB);
	Quad face;

	//////////// RIGHT && LEFT FACE
	if (dotProduct(AB, boxRef.i) < 0)
		face = getRight();
	else
		face = getLeft();

	if (face.Segment_Quad(segment, interPt, interNormal))
		return true;

	//////////// UP && BOTTOM FACE
	if (dotProduct(AB, boxRef.j) < 0)
		face = getUp();
	else
		face = getBottom();

	if (face.Segment_Quad(segment, interPt, interNormal))
		return true;

	//////////// FRONT && BACK FACE
	if (dotProduct(AB, boxRef.k) < 0)
		face = getFront();
	else
		face = getBack();

	if (face.Segment_Quad(segment, interPt, interNormal))
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