#pragma once

#include <raylib.h>

struct Application
{
	void initWindow();

	Camera3D initCamera();

	void drawGrid();

	void cameraControls();
};