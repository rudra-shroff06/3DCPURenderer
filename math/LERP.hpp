#pragma once
#include "Vector.hpp"






struct LERP {
	
	static float lerp(float p1, float t, float p2) {
		return p1 + t * (p2 - p1);
	}

	static Vector2f lerp2(const Vector2f& p1, float t, const Vector2f& p2) {
		return { lerp(p1.x, t, p2.x), lerp(p1.y, t, p2.y)};
	}

	static Vector3f lerp3(const Vector3f& p1, float t, const Vector3f& p2) {
		return { lerp(p1.x, t, p2.x), lerp(p1.y, t, p2.y), lerp(p1.z, t, p2.z) };
	}

	static Vector4f lerp4(const Vector4f& p1, float t, const Vector4f& p2) {
		return { lerp(p1.w, t, p2.w), lerp(p1.x, t, p2.x), lerp(p1.y, t, p2.y), lerp(p1.z, t, p2.z) };
	}

};