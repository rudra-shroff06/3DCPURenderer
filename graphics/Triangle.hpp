#pragma once
#include "Vertex.hpp"



//Triangles in the original mesh
struct InputTriangle {
	unsigned int v0, v1, v2; //Vertex indices
};





//Triangles Ready to Render
struct RenderTriangle {
	Vertex v0, v1, v2;
};



