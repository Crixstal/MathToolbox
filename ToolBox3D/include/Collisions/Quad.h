#pragma once

#include "Definitions.h"
#include "Referential.h"

struct Quad
{
	vec3 center;
	quat quaternion;
	vec2 extension;
	
	Quad() {};
	Quad(const vec3& c, const quat& q, const vec2& e);

	Segment getNearEdge(const vec3& externLocalPt);
	vec3 getNearVertice(const vec3& localPt, const Quad& quad);
	bool isInQuad(const vec3& point);
	bool isInQuad(const vec3& point, const Quad& quad, Segment& nearestEgde1, Segment& nearestEgde2);
	bool Segment_Quad(const Segment& segment, vec3& interPt, vec3& interNormal);
};