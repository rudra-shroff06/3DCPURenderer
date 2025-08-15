#pragma once
#include "Vector.hpp"







struct Barycentric {
	static bool calculateBarycentric(float& alpha, float& beta, float& gamma, const Vector2f& A, const Vector2f& B, const Vector2f& C, const Vector2f& P) {
		Vector2f p = P - C;
		Vector2f u = A - C;
		Vector2f v = B - C;

		float pv = p.dot(v);
		float uv = u.dot(v);
		float pu = p.dot(u);
		float vv = v.dot(v);
		float uu = u.dot(u);

		float denom = (uv * uv) - (uu * vv);
		if (fabs(denom) < 1e-6) return false;

		alpha = ((pv * uv) - (pu * vv)) / denom;
		beta = ((pu * uv) - (pv * uu)) / denom;
		gamma = 1 - alpha - beta;

		return true;
	}
};