#pragma once

#include "Definitions.h"

inline float dotProduct(const vec3& vecA, const vec3& vecB)
{
	return vecA.x * vecB.x + vecA.y * vecB.y + vecA.z * vecB.z;
};

inline float vecMagnitude(const vec3& vec)
{
	return sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2));
}

inline vec3 normalize(const vec3& vec)
{
	float mag = vecMagnitude(vec);

	if (mag == 0.f)
		return vec;

	return vec / mag;
}

inline vec3 abs(const vec3& vec)
{
	return { fabsf(vec.x), fabsf(vec.y), fabsf(vec.z) };
}

inline vec3 crossProduct(const vec3& vecA, const vec3& vecB)
{
	return	{
		vecA.y * vecB.z - vecA.z * vecB.y,
		vecA.z * vecB.x - vecA.x * vecB.z,
		vecA.x * vecB.y - vecA.y * vecB.x
	};
}

inline vec3 vecFromPt(const vec3& vecA, const vec3& vecB)
{
	return {
	vecB.x - vecA.x,
	vecB.y - vecA.y,
	vecB.z - vecA.z
	};
}

inline vec3 rotateByQuat(const vec3& v, const quat& q)
{
	vec3 result = { 0 };

	result.x = v.x * (q.x * q.x + q.w * q.w - q.y * q.y - q.z * q.z) + v.y * (2 * q.x * q.y - 2 * q.w * q.z) + v.z * (2 * q.x * q.z + 2 * q.w * q.y);
	result.y = v.x * (2 * q.w * q.z + 2 * q.x * q.y) + v.y * (q.w * q.w - q.x * q.x + q.y * q.y - q.z * q.z) + v.z * (-2 * q.w * q.x + 2 * q.y * q.z);
	result.z = v.x * (-2 * q.w * q.y + 2 * q.x * q.z) + v.y * (2 * q.w * q.x + 2 * q.y * q.z) + v.z * (q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z);

	return result;
}

inline vec3 reflect(const vec3& toReflect, const vec3& normal)
{
	return toReflect - 2.f * normal * dotProduct(toReflect, normal);
}

inline vec3 modelMatrixToPosition(const mat4& matrix)
{
	return vec3(matrix.e[3], matrix.e[7], matrix.e[11]);
}

inline vec3 modelMatrixToScale(const mat4& matrix)
{
	return (
		vecMagnitude({ matrix.e[0], matrix.e[4], matrix.e[8] }),
		vecMagnitude({ matrix.e[1], matrix.e[5], matrix.e[9] }),
		vecMagnitude({ matrix.e[2], matrix.e[6], matrix.e[10] })
		);
}

inline vec3 modelMatrixToRotation(mat4 matrix)
{
	matrix.e[3] = 0.f;
	matrix.e[7] = 0.f;
	matrix.e[11] = 0.f;

	vec3 scale = modelMatrixToScale(matrix);

	matrix.e[0] /= scale.x;
	matrix.e[4] /= scale.x;
	matrix.e[8] /= scale.x;
	matrix.e[1] /= scale.y;
	matrix.e[5] /= scale.y;
	matrix.e[9] /= scale.y;
	matrix.e[2] /= scale.z;
	matrix.e[6] /= scale.z;
	matrix.e[10] /= scale.z;

	return rotateByQuat({ 1.f, 0.f, 0.f }, quaternionFromMatrix(matrix));
}

inline vec3 getVectorProjection(float dot, const vec3& axis)
{
	return dot / vecMagnitude(axis) * axis;
}

inline vec3 getVectorProjection(const vec3& vector, const vec3& axis)
{
	return getVectorProjection(dotProduct(vector, axis), axis);
}

inline vec3 getVectorPerpendicular(const vec3& vector, const vec3& axis)
{
	return vector - getVectorProjection(vector, axis);
}


template<typename T>
vec3 operator*(const vec3& vec, const T& scale)
{
	return {
		vec.x * scale,
		vec.y * scale,
		vec.z * scale
	};
}
template<typename T>
vec3 operator*(const T& scale, const vec3& vec)
{
	return vec * scale;
}
inline vec3 operator*(const vec3& vecA, const vec3& vecB)
{
	return {
		vecB.x * vecA.x,
		vecB.y * vecA.y,
		vecB.z * vecA.z
	};
}

template<typename T>
vec3 operator/(const vec3& vec, const T& k)
{
	if (k == 0.f)
		return { 0.f, 0.f, 0.f };

	T quotient = 1.f / k;

	return {
		vec.x * quotient,
		vec.y * quotient,
		vec.z * quotient
	};
}

inline vec3 operator+(const vec3& vecA, const vec3& vecB)
{
	return {
		vecA.x + vecB.x,
		vecA.y + vecB.y,
		vecA.z + vecB.z
	};
};
inline vec3 operator+(const vec3& vec, const float& k)
{
	return {
		k + vec.x,
		k + vec.y,
		k + vec.z
	};
};
inline vec3 operator+(const float& k, const vec3& vec)
{
	return {
		k + vec.x,
		k + vec.y,
		k + vec.z
	};
};

inline vec3 operator-(const vec3& vecA, const vec3& vecB)
{
	return {
		vecA.x - vecB.x,
		vecA.y - vecB.y,
		vecA.z - vecB.z
	};
};
inline vec3 operator-(const vec3& vec, const float& k)
{
	return {
		k - vec.x,
		k - vec.y,
		k - vec.z
	};
};
inline vec3 operator-(const vec3& vecA)
{
	return {
		-vecA.x,
		-vecA.y,
		-vecA.z
	};
};

inline vec3 operator^(const vec3& vecA, const vec3& vecB) // Cross product
{
	return
	{
		vecA.y * vecB.z - vecA.z * vecB.y,
		vecA.z * vecB.x - vecA.x * vecB.z,
		vecA.x * vecB.y - vecA.y * vecB.x
	};
}

inline vec3 operator+=(vec3& vecA, const vec3& vecB)
{
	return {
		vecA.x += vecB.x,
		vecA.y += vecB.y,
		vecA.z += vecB.z
	};
};

inline vec3 operator-=(vec3& vecA, const vec3& vecB)
{
	return {
		vecA.x -= vecB.x,
		vecA.y -= vecB.y,
		vecA.z -= vecB.z
	};
};

inline bool operator==(vec3& vecA, const vec3& vecB)
{
	return (
		vecA.x == vecB.x &&
		vecA.y == vecB.y &&
		vecA.z == vecB.z
		);
}

template<typename T>
vec3& operator*=(vec3& vec, const T& k)
{
	return vec *= k;
}