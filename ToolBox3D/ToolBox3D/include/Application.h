#pragma once

#include <raylib.h>

#include "Plane.h"
#include "Quad.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Box.h"

struct Application
{
	enum class State
	{
		PLANE,
		SPHERE,
		QUAD,
		CYLINDER,
		BOX,
		ROUND_BOX
	};

	int stateChanger = 0;
	State state = State::PLANE;
	
	void initWindow();
	Camera3D initCamera();
	void drawGrid();
	void cameraControls();

	void changeMode();
	void drawIntersection();
};