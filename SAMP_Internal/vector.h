#pragma once
#include <cmath>
struct Vector2 { float x, y; };

class Vector3
{
public:

	float x, y, z;

	Vector3() {};
	Vector3(const float x, const float y, const float z) : x(x), y(y), z(z) {}
	Vector3 operator + (const Vector3& rhs) const { return Vector3(x + rhs.x, y + rhs.y, z + rhs.z); }
	Vector3 operator - (const Vector3& rhs) const { return Vector3(x - rhs.x, y - rhs.y, z - rhs.z); }
	Vector3 operator * (const float& rhs) const { return Vector3(x * rhs, y * rhs, z * rhs); }
	Vector3 operator / (const float& rhs) const { return Vector3(x / rhs, y / rhs, z / rhs); }
	Vector3& operator += (const Vector3& rhs) { return *this = *this + rhs; }
	Vector3& operator -= (const Vector3& rhs) { return *this = *this - rhs; }
	Vector3& operator *= (const float& rhs) { return *this = *this * rhs; }
	Vector3& operator /= (const float& rhs) { return *this = *this / rhs; }
	float length() const { return sqrtf(x * x + y * y + z * z); }
	Vector3 normalize() const { return *this * (1 / length()); }
	float distance(const Vector3& rhs) const { return (*this - rhs).length(); }
	void correctAngles() { while (y < -3.14159265358f) y += 6.28318530717f; while (y > 3.14159265358f) y -= 6.28318530717f; if (x > 1.57079632679f) x = 1.57079632679f; if (x < -1.57079632679f) x = -1.57079632679f; }
};

struct Vector4 {
	float x, y, z, w;
};