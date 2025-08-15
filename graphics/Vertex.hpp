#pragma once
#include "../math/Vector.hpp"



struct Vertex {
	Vector3f position;
	Vector3f color;
	Vector2f uv;
	float w;
	float invW;
};