#pragma once
#include "Vertex.hpp"
#include "Triangle.hpp"
#include "ClipperUtils.hpp"
#include <vector>
#include <iostream>









struct Clipper {
	static std::vector<RenderTriangle> applyClip(const RenderTriangle& tri) {
		std::vector<RenderTriangle> finalTriangles;
		//std::cout << "Hello 4\n";
		std::vector<Vertex> input = { tri.v0, tri.v1, tri.v2 } , output;
		clipAgainstLeftPlane(input, output);
		input = output;
		clipAgainstUpPlane(input, output);
		input = output;
		clipAgainstRightPlane(input, output);
		input = output;
		clipAgainstDownPlane(input, output);
		input = output;
		clipAgainstFarPlane(input, output);
		input = output;
		clipAgainstNearPlane(input, output);
		input.clear();

		//std::cout << "Hello 5\n";
		//std::cout << output.size() << '\n';
		for (int i = 1; i < static_cast<int>(output.size()) - 1; i++) {
			//std::cout << "Hello 6\n";
			RenderTriangle t;
			t.v0 = output[0];
			t.v1 = output[i];
			t.v2 = output[i + 1];
			finalTriangles.push_back(t);
		}
		//std::cout << "Hello 3\n";
		//std::cout << finalTriangles[0].v1.position.y << '\n';
		return finalTriangles;

	}
};







