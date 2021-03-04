#pragma once

#include <raylib.h>

#include "Plane.h"
#include "Quad.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Box.h"
#include "Capsule.h"

struct Application
{
	enum class State
	{
		PLANE,
		SPHERE,
		QUAD,
		CYLINDER,
		CAPSULE,
		BOX,
		ROUND_BOX,
		BOUNCING_BALL
	};

	int stateChanger = 3;
	State state;
	bool isInfinite = false;
	
	void initWindow();
	Camera3D initCamera();
	void drawGrid();
	void cameraControls();

	void changeMode();
	void drawIntersection();
};