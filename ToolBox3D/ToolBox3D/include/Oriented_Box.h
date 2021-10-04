#pragma once

#include "Maths.h"
#include "Box.h"
#include "Sphere.h"

struct Oriented_Box
{
	bool Box_SphereAABB();
	bool Box_Sphere();
	bool Box_Box();
};