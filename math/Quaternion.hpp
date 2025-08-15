#pragma once
#include "Vector.hpp"




struct Quaternion {
	float w, x, y, z;


	Quaternion() : w(1), x(0), y(0), z(0) {}
	Quaternion(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {}
	Quaternion(float w, Vector3f v) : w(w), x(v.x), y(v.y), z(v.z) {}


	Quaternion operator*(const Quaternion& other) const {
		return {
			w * other.w - x * other.x - y * other.y - z * other.z,
			x * other.w + w * other.x - z * other.y + y * other.z,
			y * other.w + z * other.x + w * other.y - x * other.z,
			z * other.w - y * other.x + x * other.y + w * other.z
		};
	}


	Quaternion operator*(const Vector3f& other) const {
		Quaternion q(0, other);
		return (*this) * q;
	}


	Quaternion conjugate() const {
		return {
			w,
			-x,
			-y,
			-z
		};
	}

	Quaternion inverse() const {
		float Sqmagnitude = w * w + x * x + y * y + z * z;
		return {
			w / Sqmagnitude,
			-x / Sqmagnitude,
			-y / Sqmagnitude,
			-z / Sqmagnitude
		};
	}


	Vector3f getVectorPart() {
		return {x, y, z};
	}


};





inline Quaternion operator*(const Vector3f& vec, const Quaternion& q) {
	Quaternion p(0, vec);
	return p * q;
}