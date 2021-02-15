#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

#include <raylib.h>
#include <rlgl.h>

struct Segment
{
	Vector3 ptA;
	Vector3 ptB;
};

inline float dotProduct(const Vector3& vec1, const Vector3& vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
};

inline float vectorMagnitude(const Vector3& vec)
{
	return sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2));
}

inline Vector3 clamp(Vector3& vec, const float& min, const float& max)
{
	if (vec.x > max)
		vec.x = max;
	else if (vec.x < min)
		vec.x = min;

	if (vec.y > max)
		vec.y = max;
	else if (vec.y < min)
		vec.y = min;

	if (vec.z > max)
		vec.z = max;
	else if (vec.z < min)
		vec.z = min;
}

inline Vector3 normalize(const Vector3& vec)
{
	return {
		vec.x / vectorMagnitude(vec),
		vec.y / vectorMagnitude(vec),
		vec.z / vectorMagnitude(vec)
	};
}

inline Vector3 vectorProduct(const Vector3& vecA, const Vector3& vecB)
{
	return	{
		vecA.y * vecB.z - vecA.z * vecB.y,
		vecA.z * vecB.x - vecA.x * vecB.z,
		vecA.x * vecB.y - vecA.y * vecB.x
	};
}

inline Vector3 vecFromPt(const Vector3& vecA, const Vector3& vecB)
{
	return {
	vecB.x - vecA.x,
	vecB.y - vecA.y,
	vecB.z - vecA.z
	};
}

inline Vector3 operator*(const Vector3& vec, const float& k)
{
	return { 
		k * vec.x, 
		k * vec.y,
		k * vec.z
	};
};

inline Vector3 operator*(const float& k, const Vector3& vec)
{
	return {
		k * vec.x,
		k * vec.y,
		k * vec.z
	};
};

inline Vector3 operator*(const Vector3& vecA, const Vector3& vecB)
{
	return {
	vecB.x * vecA.x,
	vecB.y * vecA.y,
	vecB.z * vecA.z
	};
}

inline Vector3 operator+(const Vector3& vecA, const Vector3& vecB)
{ 
	return {
		vecA.x + vecB.x,
		vecA.y + vecB.y,
		vecA.z + vecB.z
	};
};

inline Vector3 operator-(const Vector3& vecA, const Vector3& vecB)
{
	return {
		vecA.x - vecB.x,
		vecA.y - vecB.y,
		vecA.z - vecB.z
	};
};

inline Vector3 operator-(const Vector3& vecA)
{
	return {
		-vecA.x,
		-vecA.y,
		-vecA.z
	};
};