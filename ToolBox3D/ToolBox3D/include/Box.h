#pragma once

#include "Maths.h"
#include "Quad.h"
#include "Referential.h"

struct Round_Box;

struct Box
{
	Vector3 center;
	Vector3 size;
	Quaternion quaternion;

	Box(const Vector3& c, const Vector3& s, const Quaternion& q);

	operator Round_Box() const;

	void myDrawBox(const Color& color = GREEN);
	bool isPointInsideBox(const Vector3& point);
	Vector3 boxVerticeLocalToGlobal(const Vector3& vertice);
	Vector3 getNearVertice(const Vector3& globalPt, Vector3& localNearVertice);
    Quad getRight() const;
	Quad getLeft() const;
	Quad getFront() const;
	Quad getBack() const;
	Quad getUp() const;
	Quad getBottom() const;
	bool Segment_Box(const Segment& segment, Vector3& interPt, Vector3& interNormal, Quad* quadInter);
	void drawIntersection(const Segment& segment, Vector3& interPt, Vector3& interNormal, Color color = GREEN);
};

inline Vector3 Vec3RotateByQuaternion(Vector3 vector, Quaternion q)
	{
		float qx_square = q.x * q.x, qy_square = q.y * q.y, qz_square = q.z * q.z, qw_square = q.w * q.w;

		// From operation " v' = q(rot) * q(vector) * q(rot).conjugate "
		return    {
			// X coord
			vector.x * (qx_square - qy_square - qz_square + qw_square) +
			vector.y * (2.0f * q.x * q.y - 2.0f * q.w * q.z) +
			vector.z * (2.0f * q.x * q.z + 2.0f * q.w * q.y),
			// Y coord
			vector.x * (2.0f * q.w * q.z + 2.0f * q.x * q.y) +
			vector.y * (-qx_square + qy_square - qz_square + qw_square) +
			vector.z * (-2.0f * q.w * q.x + 2.0f * q.y * q.z),
			// Z coord
			vector.x * (-2.0f * q.w * q.y + 2.0f * q.x * q.z) +
			vector.y * (2.0f * q.w * q.x + 2.0f * q.y * q.z) +
			vector.z * (-qx_square - qy_square + qz_square + qw_square)
		};
	}