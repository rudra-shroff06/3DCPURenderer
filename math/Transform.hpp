#pragma once
#include "Vector.hpp"
#include <cmath>

struct Transform {
	Vector3f translate;
	Vector3f rotation;
	Vector3f scale;


	Transform() {
		this->translate = { 0, 0, 0 };
		this->rotation = { 0, 0, 0 };
		this->scale = { 1, 1, 1 };
	}


	//Checked Works Perfect
	Vector3f applyModel(const Vector3f& p) const {
		Vector3f result = { scale.x * p.x, scale.y * p.y, scale.z * p.z };
		float cosA = cos(rotation.x), sinA = sin(rotation.x);
		float cosB = cos(rotation.y), sinB = sin(rotation.y);
		float cosC = cos(rotation.z), sinC = sin(rotation.z);

		result = {
			cosC * cosB * result.x + (cosC * sinB * sinA - sinC * cosA) * result.y + (sinC * sinA + cosC * sinB * cosA) * result.z,
			sinC * cosB * result.x + (cosC * cosA + sinC * sinB * sinA) * result.y + (sinC * sinB * cosA - cosC * sinA) * result.z,
			-sinB * result.x + cosB * sinA * result.y + cosB * cosA * result.z
		};

		result = result + translate;

		return result;
	}

};