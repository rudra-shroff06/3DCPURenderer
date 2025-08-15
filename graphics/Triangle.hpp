#pragma once
#include "Vertex.hpp"



//Triangles in the original mesh
struct InputTriangle {
	unsigned int v0, v1, v2; //Vertex indices
	InputTriangle(unsigned int v0, unsigned int v1, unsigned int v2) : v0(v0), v1(v1), v2(v2) {}
};





//Triangles Ready to Render
struct RenderTriangle {
	Vertex v0, v1, v2;
};



