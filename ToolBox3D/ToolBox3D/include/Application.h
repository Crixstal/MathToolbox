#pragma once

#include <raylib.h>

#include "Plane.h"
#include "Sphere.h"
#include "Quad.h"
#include "Cylinder.h"
#include "Capsule.h"
#include "Box.h"
#include "Round_Box.h"

struct Application
{
	enum class State
	{
		PLANE,
		QUAD,
		SPHERE,
		CYLINDER,
		CAPSULE,
		BOX,
		ROUND_BOX,
		BOUNCING_BALL
	};

	int stateChanger = 0;
	State state;
	bool isInfinite = false;
	
	void initWindow();
	Camera3D initCamera();
	void drawGrid();
	void cameraControls();

	void changeMode();
	void drawIntersection();
	void move(Vector3& toMove, Quaternion& quaternion);
};