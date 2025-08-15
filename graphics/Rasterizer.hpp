#pragma once
#include "Vertex.hpp"
#include "Triangle.hpp"
#include "FrameBuffer.hpp"
#include "../math/Barycentric.hpp"
#include <algorithm>




//Converts ndc to viewport and rasterizes and puts the triangle into the framebuffer


struct Rasterizer {

	FrameBuffer* framebuffer;

	Rasterizer(int width, int height) {
		framebuffer = new FrameBuffer(width, height);
	}

	void rasterizeTriangle(const RenderTriangle& tri) {
		Vertex v0 = tri.v0;
		Vertex v1 = tri.v1;
		Vertex v2 = tri.v2;
		//std::cout << v1.position.y << '\n';
		//Convert to ndc then viewport
		v0.position.x = v0.position.x * (v0.invW);
		v0.position.y = v0.position.y * (v0.invW);
		v1.position.x = v1.position.x * (v1.invW);
		v1.position.y = v1.position.y * (v1.invW);
		v2.position.x = v2.position.x * (v2.invW);
		v2.position.y = v2.position.y * (v2.invW);
		//std::cout << v1.position.y << '\n';

		v0.position.x = (framebuffer->width * (v0.position.x + 1.f)) * .5f;
		v1.position.x = (framebuffer->width * (v1.position.x + 1.f)) * .5f;
		v2.position.x = (framebuffer->width * (v2.position.x + 1.f)) * .5f;
		v0.position.y = (framebuffer->height * (1.f - v0.position.y)) * .5f;
		v1.position.y = (framebuffer->height * (1.f - v1.position.y)) * .5f;
		v2.position.y = (framebuffer->height * (1.f - v2.position.y)) * .5f;
		
		//std::cout << v1.position.y << '\n';
		
		
		int minX = std::max(0, (int)std::floor(std::min(v0.position.x, std::min(v1.position.x, v2.position.x))));
		int minY = std::max(0, (int)std::floor(std::min(v0.position.y, std::min(v1.position.y, v2.position.y))));
		int maxX = std::min(framebuffer->width - 1, (int)std::ceil(std::max(v0.position.x, std::max(v1.position.x, v2.position.x))));
		int maxY = std::min(framebuffer->height - 1, (int)std::ceil(std::max(v0.position.y, std::max(v1.position.y, v2.position.y))));



		for (int y = minY; y <= maxY; y++) {
			for (int x = minX; x <= maxX; x++) {

				float px = x + .5f;
				float py = y + .5f;

				float alpha, beta, gamma;

				if (!Barycentric::calculateBarycentric(alpha, beta, gamma, { v0.position.x, v0.position.y }, { v1.position.x, v1.position.y }, { v2.position.x, v2.position.y }, { px, py })) {
					return;
				}

				const float EPS = -1e-5f;

				if (alpha < EPS || beta < EPS || gamma < EPS) continue;



				float interpolatedinvW = ((v0.invW * alpha) + (v1.invW * beta) + (v2.invW * gamma));
				float interpolatedW = 1 / interpolatedinvW;
				Vector3f interpolatedcolor = ((v0.color * v0.invW * alpha) + (v1.color * v1.invW * beta) + (v2.color * v2.invW * gamma)) * interpolatedW;
				Vector3f pixelColor = { std::clamp(interpolatedcolor.x, 0.f, 1.f), std::clamp(interpolatedcolor.y, 0.f, 1.f) , std::clamp(interpolatedcolor.z, 0.f, 1.f) };
				
				Vector2f interpolatedUV = ((v0.uv * v0.invW * alpha) + (v1.uv * v1.invW * beta) + (v2.uv * v2.invW * gamma)) * interpolatedW;
				
				
				float interpolatedz_ndc = ((v0.position.z * v0.invW * alpha) + (v1.position.z * v1.invW * beta) + (v2.position.z * v2.invW * gamma));


				float depth = (interpolatedz_ndc + 1) * .5f;

				framebuffer->setPixel(framebuffer->width - 1 - x, framebuffer->height - 1- y, pixelColor, depth);

			}
		}

		













	}
};









