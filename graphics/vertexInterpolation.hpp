#pragma once
#include "Vertex.hpp"
#include "../math/LERP.hpp"






Vertex interpolateVertex(const Vertex& v1, float t, const Vertex& v2) {
	Vertex result;
	result.position = LERP::lerp3(v1.position, t, v2.position);
	result.color = LERP::lerp3(v1.color, t, v2.color);
	result.w = LERP::lerp(v1.w, t, v2.w);
	result.invW = 1.f / result.w;
	return result;
}






