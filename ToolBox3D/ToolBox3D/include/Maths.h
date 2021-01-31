#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

#include <raylib.h>

inline float dotProduct(Vector3& vec1, Vector3& vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
};

inline float vectorMagnitude(Vector3 vec)
{
	return sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2));
}

inline Vector3 normalize(Vector3 vec)
{
	return {
		vec.x / vectorMagnitude(vec),
		vec.y / vectorMagnitude(vec),
		vec.z / vectorMagnitude(vec)
	};
}

inline Vector3 vectorProduct(Vector3 vecA, Vector3 vecB)
{
	return	{
		vecA.y * vecB.z - vecA.z * vecB.y,
		vecA.z * vecB.x - vecA.x * vecB.z,
		vecA.x * vecB.y - vecA.y * vecB.x
	};
}

inline Vector3 operator*(Vector3 vec, float k)
{
	return { 
		k * vec.x, 
		k * vec.y,
		k * vec.z
	};
};

inline Vector3 operator+(Vector3 vecA, Vector3 vecB)
{ 
	return {
		vecA.x + vecB.x,
		vecA.y + vecB.y,
		vecA.z + vecB.z
	};
};

inline Vector3 operator-(Vector3 vecA, Vector3 vecB) 
{ 
	return { 
		vecB.x - vecA.x,
		vecB.y - vecA.y,
		vecB.z - vecA.z 
	}; 
};