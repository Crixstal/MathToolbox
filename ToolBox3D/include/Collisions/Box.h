#pragma once

#include "Definitions.h"
#include "Quad.h"
#include "Referential.h"

struct Round_Box;

struct Box
{
	vec3 center;
	vec3 size;
	quat quaternion;

	Box(const vec3& c, const vec3& s, const quat& q);

	operator Round_Box() const;

	bool isPointInsideBox(const vec3& point);
	vec3 boxVerticeLocalToGlobal(const vec3& vertice);
	vec3 getNearVertice(const vec3& globalPt, vec3& localNearVertice);
    Quad getRight() const;
	Quad getLeft() const;
	Quad getFront() const;
	Quad getBack() const;
	Quad getUp() const;
	Quad getBottom() const;
	bool Segment_Box(const Segment& segment, vec3& interPt, vec3& interNormal, Quad* quadInter);
};