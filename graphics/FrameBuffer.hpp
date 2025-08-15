#pragma once
#include "../math/Vector.hpp"
#include <vector>
#include <limits>
#include <cstdint>
#include <fstream>
#include <iostream>

struct FrameBuffer {
	int width;
	int height;
	std::vector<Vector3f> frameBuffer;
	std::vector<float> depthBuffer;

	FrameBuffer(int width, int height) : width(width), height(height) {
		frameBuffer.resize(width * height, Vector3f(0.0f, 0.0f, 0.0f));
        depthBuffer.resize(width * height, std::numeric_limits<float>::max());

	}



	void clearBuffer(Vector3f color) {
		std::fill(frameBuffer.begin(), frameBuffer.end(), color);
		std::fill(depthBuffer.begin(), depthBuffer.end(), std::numeric_limits<float>::max());
	}


	void setPixel(int x, int y, Vector3f color, float depth) {
		int index = y * width + x;
		if (depth < depthBuffer[index]) {
			depthBuffer[index] = depth;
			frameBuffer[index] = color;
		}

	}

	Vector3f getPixel(int x, int y) const {
		int index = y * width + x;
		return frameBuffer[index];
	}

	//Tempfunction
	void Export(const char* path) const {
		std::ofstream f;
		f.open(path, std::ios::out | std::ios::binary);

		if (!f.is_open()) {
			std::cout << "File Cannot be Opened\n";
		}

		unsigned char bmpPad[3] = { 0, 0, 0 };
		const int paddingAmount = ((4 - (width * 3) % 4) % 4);

		const int fileHeaderSize = 14;
		const int informationHeaderSize = 40;
		const int fileSize = fileHeaderSize + informationHeaderSize + width * height * 3 + paddingAmount * height;

		unsigned char fileHeader[fileHeaderSize];


		fileHeader[0] = 'B';
		fileHeader[1] = 'M';

		fileHeader[2] = fileSize;
		fileHeader[3] = fileSize >> 8;
		fileHeader[4] = fileSize >> 16;
		fileHeader[5] = fileSize >> 24;

		fileHeader[6] = 0;
		fileHeader[7] = 0;
		fileHeader[8] = 0;
		fileHeader[9] = 0;

		fileHeader[10] = fileHeaderSize + informationHeaderSize;
		fileHeader[11] = 0;
		fileHeader[12] = 0;
		fileHeader[13] = 0;

		unsigned char informationHeader[informationHeaderSize];
		
		informationHeader[0] = informationHeaderSize;
		informationHeader[1] = 0;
		informationHeader[2] = 0;
		informationHeader[3] = 0;

		informationHeader[4] = width;
		informationHeader[5] = width >> 8;
		informationHeader[6] = width >> 16;
		informationHeader[7] = width >> 24;

		informationHeader[8] = height;
		informationHeader[9] = height >> 8;
		informationHeader[10] = height >> 16;
		informationHeader[11] = height >> 24;

		informationHeader[12] = 1;
		informationHeader[13] = 0;

		informationHeader[14] = 24;
		informationHeader[15] = 0;

		informationHeader[16] = 0;
		informationHeader[17] = 0;
		informationHeader[18] = 0;
		informationHeader[19] = 0;

		informationHeader[20] = 0;
		informationHeader[21] = 0;
		informationHeader[22] = 0;
		informationHeader[23] = 0;
		
		informationHeader[24] = 0;
		informationHeader[25] = 0;
		informationHeader[26] = 0;
		informationHeader[27] = 0;

		informationHeader[28] = 0;
		informationHeader[29] = 0;
		informationHeader[30] = 0;
		informationHeader[31] = 0;

		informationHeader[32] = 0;
		informationHeader[33] = 0;
		informationHeader[34] = 0;
		informationHeader[35] = 0;

		informationHeader[36] = 0;
		informationHeader[37] = 0;
		informationHeader[38] = 0;
		informationHeader[39] = 0;

		f.write(reinterpret_cast<char*>(fileHeader), fileHeaderSize);
		f.write(reinterpret_cast<char*>(informationHeader), informationHeaderSize);

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				unsigned char r = static_cast<unsigned char>(getPixel(x, y).x * 255.0f);
				unsigned char g = static_cast<unsigned char>(getPixel(x, y).y * 255.0f);
				unsigned char b = static_cast<unsigned char>(getPixel(x, y).z * 255.0f);

				unsigned char color[] = { b, g, r };

				f.write(reinterpret_cast<char*>(color), 3);
			}

			f.write(reinterpret_cast<char*>(bmpPad), paddingAmount);
		}

		f.close();

		//std::cout << "File Created\n";
	}

};