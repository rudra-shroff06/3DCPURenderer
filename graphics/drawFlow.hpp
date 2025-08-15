#pragma once
#include "Model.hpp"
#include "Mesh.hpp"
#include "FrameBuffer.hpp"
#include "Clipper.hpp"
#include "Vertex.hpp"
#include "Triangle.hpp"
#include "Rasterizer.hpp"
#include "../math/Transform.hpp"
#include "../camera/FPSCamera.hpp"
#include <iostream>


struct DrawToImage {









	static void draw(Model MyModel, const Camera& view, Rasterizer myRasterizer) {
		
		//Converting InputTriangles to RenderTriangles

		for (auto& it : MyModel.mMesh.triangleBuffer) {

			Vertex v0 = MyModel.mMesh.vertexBuffer[it.v0];
			Vertex v1 = MyModel.mMesh.vertexBuffer[it.v1];
			Vertex v2 = MyModel.mMesh.vertexBuffer[it.v2];


			
			//Transform from Model to World

			v0.position = MyModel.transform.applyModel(v0.position);
			v1.position = MyModel.transform.applyModel(v1.position);
			v2.position = MyModel.transform.applyModel(v2.position);

			//std::cout << v1.position.y << '\n';


			v0.position = view.applyView(v0.position);
			v1.position = view.applyView(v1.position);
			v2.position = view.applyView(v2.position);

			//std::cout << v1.position.y << '\n';

			Vector4f p0 = view.applyProjection(v0.position);
			Vector4f p1 = view.applyProjection(v1.position);
			Vector4f p2 = view.applyProjection(v2.position);

			//std::cout << p1.z << '\n';

			v0.position = { p0.x, p0.y, p0.z };
			v1.position = { p1.x, p1.y, p1.z };
			v2.position = { p2.x, p2.y, p2.z };

			//std::cout << v1.position.y << '\n';
			//std::cout << p1.w << '\n';
			v0.w = p0.w;
			v0.invW = 1 / p0.w;
			v1.w = p1.w;
			v1.invW = 1 / p1.w;
			v2.w = p2.w;
			v2.invW = 1 / p2.w;

			//std::cout << "hello 1\n";
			RenderTriangle tri;
			tri.v0 = v0;
			tri.v1 = v1;
			tri.v2 = v2;


			//Clipping Part
			std::vector<RenderTriangle> finalTriangles = Clipper::applyClip(tri);
			//std::cout << "Hello 2\n";

			//Rasterization
			for (auto& it : finalTriangles) {
				myRasterizer.rasterizeTriangle(it);
			}




		}
		
		myRasterizer.framebuffer->Export("TheFirst.bmp");





	}















};