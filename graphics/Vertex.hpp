#pragma once
#include "../math/Vector.hpp"



struct Vertex {
	Vector3f position;
	Vector3f color;
	float w;
	float invW;
};