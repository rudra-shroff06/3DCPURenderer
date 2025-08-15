#pragma once
#include "Vertex.hpp"
#include "Triangle.hpp"
#include <vector>




struct Mesh {
	std::vector<Vertex> vertexBuffer;
	std::vector<InputTriangle> triangleBuffer;
};