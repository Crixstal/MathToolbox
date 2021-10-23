#pragma once

#include "Maths.h"
#include "Referential.h"

struct Quad
{
	Vector3 center;
	Quaternion quaternion;
	Vector2 extension;
	
	Quad() {};
	Quad(const Vector3& c, const Quaternion& q, const Vector2& e);

	void myDrawQuad(const Color& color = GREEN);
	Segment getNearEdge(const Vector3& externLocalPt);
	Vector3 getNearVertice(const Vector3& localPt, const Quad& quad);
	bool isInQuad(const Vector3& point);
	bool isInQuad(const Vector3& point, const Quad& quad, Segment& nearestEgde1, Segment& nearestEgde2);
	bool Segment_Quad(const Segment& segment, Vector3& interPt, Vector3& interNormal);
	void drawIntersection(const Segment& segment, Vector3& interPt, Vector3& interNormal, Color color = GREEN);
};