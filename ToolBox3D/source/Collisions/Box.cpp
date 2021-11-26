#include "Box.h"
#include "Round_Box.h"

#include "Quaternion.h" // already include Mat4 which include Vector3

Box::Box(const vec3& c, const vec3& s, const quat& q)
{
	center = c;
	size = s;
	quaternion = q;
}

Box::operator Round_Box() const
{
	return { center, size, quaternion, 0.f };
}

bool Box::isPointInsideBox(const vec3& point)
{
	Referential ref (center, quaternion);

	// Find box referential
	vec3 centerPoint = point - center;

	// Compute dot products between box's center-point vector and box's unit vector
	centerPoint = { dotProduct(centerPoint, ref.i), dotProduct(centerPoint, ref.j), dotProduct(centerPoint, ref.k) };
	// Compare dot with box extensions, since dot products are point projection on xyz plane according to box referential
	return ((centerPoint.x <= size.x && centerPoint.x >= -size.x)
		&& (centerPoint.y <= size.y && centerPoint.y >= -size.y)
		&& (centerPoint.z <= size.z && centerPoint.z >= -size.z));
}

vec3 Box::boxVerticeLocalToGlobal(const vec3& vertice)
{
	vec3 pt = vertice;
	return rotateByQuat((vertice * size), quaternion) + center;
}

vec3 Box::getNearVertice(const vec3& globalPt, vec3& localNearVertice)
{
	// Find box referential
	vec3 centerPoint = globalPt - center;
	Referential localRef(center, quaternion);
	// As in first "inside box", compute point projection on box unit plane
	centerPoint = vec3{ dotProduct(centerPoint, localRef.i), dotProduct(centerPoint, localRef.j), dotProduct(centerPoint, localRef.k) };

	localNearVertice = {
		centerPoint.x < 0 ? -1.f : 1.f,
		centerPoint.y < 0 ? -1.f : 1.f,
		centerPoint.z < 0 ? -1.f : 1.f
	};

	return boxVerticeLocalToGlobal(localNearVertice);
}

Quad Box::getRight() const
{
	quat qdQuaternion = quaternion * quatFromAxisAngle({0.f, 0.f, 1.f}, -PI / 2);
	vec3 qdCenter = rotateByQuat(vec3{ 1.f, 0.f, 0.f } *size, quaternion) + center;

	return { qdCenter, qdQuaternion, {size.y, size.z} };
}

Quad Box::getLeft() const
{
	quat qdQuaternion = quaternion * quatFromAxisAngle({0.f, 0.f, 1.f}, PI / 2);
	vec3 qdCenter = rotateByQuat(vec3{ -1.f, 0.f, 0.f } *size, quaternion) + center;

	return { qdCenter, qdQuaternion, {size.y, size.z} };
}

Quad Box::getFront() const
{
	quat qdQuaternion = quaternion * quatFromAxisAngle({1.f, 0.f, 0.f}, PI / 2);
	vec3 qdCenter = rotateByQuat(vec3{ 0.f, 0.f, 1.f } *size, quaternion) + center;

	return { qdCenter, qdQuaternion, {size.x, size.y} };
}

Quad Box::getBack() const
{
	quat qdQuaternion = quaternion * quatFromAxisAngle({1.f, 0.f, 0.f}, -PI / 2);
	vec3 qdCenter = rotateByQuat(vec3{ 0.f, 0.f, -1.f } *size, quaternion) + center;

	return { qdCenter, qdQuaternion, {size.x, size.y} };
}

Quad Box::getUp() const
{
	quat qdQuaternion = quaternion * quatFromAxisAngle({1.f, 0.f, 0.f}, 0.f);
	vec3 qdCenter = rotateByQuat(vec3{ 0.f, 1.f, 0.f } *size, quaternion) + center;

	return { qdCenter, qdQuaternion, {size.x, size.z} };
}

Quad Box::getBottom() const
{
	quat qdQuaternion = quaternion * quatFromAxisAngle({ 1.f, 0.f, 0.f }, PI);
	vec3 qdCenter = rotateByQuat(vec3{ 0.f, -1.f, 0.f } *size, quaternion) + center;

	return { qdCenter, qdQuaternion, {size.x, size.z} };
}

bool Box::Segment_Box(const Segment& segment, vec3& interPt, vec3& interNormal, Quad* quadInter)
{
	if (isPointInsideBox(segment.ptA)) 
		return false;

	Referential boxRef (center, quaternion);
	vec3 AB = vecFromPt(segment.ptA, segment.ptB);
	Quad face;

	//////////// RIGHT && LEFT FACE
	if (dotProduct(AB, boxRef.i) < 0)
		face = getRight();
	else
		face = getLeft();

	if (quadInter)
		*quadInter = face;

	if (face.Segment_Quad(segment, interPt, interNormal))
		return true;

	//////////// UP && BOTTOM FACE
	if (dotProduct(AB, boxRef.j) < 0)
		face = getUp();
	else
		face = getBottom();

	if (quadInter)
		*quadInter = face;

	if (face.Segment_Quad(segment, interPt, interNormal))
		return true;

	//////////// FRONT && BACK FACE
	if (dotProduct(AB, boxRef.k) < 0)
		face = getFront();
	else
		face = getBack();

	if (quadInter)
		*quadInter = face;

	if (face.Segment_Quad(segment, interPt, interNormal))
		return true;

	return false;
}