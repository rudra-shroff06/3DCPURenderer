#pragma once
#include "Vertex.hpp"
#include "vertexInterpolation.hpp"
#include <vector>



bool clipsLeftPlane(const Vertex& v) {
	if (v.position.x < -v.w) {
		return true;
	}

	return false;
}


bool clipsRightPlane(const Vertex& v) {
	if (v.position.x > v.w) {
		return true;
	}

	return false;
}


bool clipsUpPlane(const Vertex& v) {
	if (v.position.y > v.w) {
		return true;
	}

	return false;
}


bool clipsDownPlane(const Vertex& v) {
	if (v.position.y < -v.w) {
		return true;
	}

	return false;
}


bool clipsFarPlane(const Vertex& v) {
	if (v.position.z > v.w) {
		return true;
	}

	return false;
}


bool clipsNearPlane(const Vertex& v) {
	if (v.position.z < -v.w) {
		return true;
	}

	return false;
}





void clipAgainstLeftPlane(const std::vector<Vertex>& input, std::vector<Vertex>& output) {
	
	output.clear();
	
	for (int i = 0; i < input.size(); i++) {
		Vertex curr = input[i];
		Vertex prev = input[(i + input.size() - 1) % input.size()];


		float t = -(prev.position.x + prev.w) / ((curr.position.x + curr.w) - (prev.position.x + prev.w));
		if (!clipsLeftPlane(prev) && !clipsLeftPlane(curr)) {
			output.push_back(curr);
		}

		else if (!clipsLeftPlane(prev) && clipsLeftPlane(curr)) {
			//add the intersection
			Vertex intersection = interpolateVertex(prev, t, curr);
			output.push_back(intersection);
		}

		else if (clipsLeftPlane(prev) && !clipsLeftPlane(curr)) {
			//add intersection and curr
			Vertex intersection = interpolateVertex(prev, t, curr);
			output.push_back(intersection);
			output.push_back(curr);
		}

	}

}


void clipAgainstRightPlane(const std::vector<Vertex>& input, std::vector<Vertex>& output) {

	output.clear();

	for (int i = 0; i < input.size(); i++) {
		Vertex curr = input[i];
		Vertex prev = input[(i + input.size() - 1) % input.size()];


		float t = -(prev.position.x - prev.w) / ((curr.position.x - curr.w) - (prev.position.x - prev.w));
		if (!clipsRightPlane(prev) && !clipsRightPlane(curr)) {
			output.push_back(curr);
		}

		else if (!clipsRightPlane(prev) && clipsRightPlane(curr)) {
			//add the intersection
			Vertex intersection = interpolateVertex(prev, t, curr);
			output.push_back(intersection);
		}

		else if (clipsRightPlane(prev) && !clipsRightPlane(curr)) {
			//add intersection and curr
			Vertex intersection = interpolateVertex(prev, t, curr);
			output.push_back(intersection);
			output.push_back(curr);
		}

	}

}




void clipAgainstUpPlane(const std::vector<Vertex>& input, std::vector<Vertex>& output) {

	output.clear();

	for (int i = 0; i < input.size(); i++) {
		Vertex curr = input[i];
		Vertex prev = input[(i + input.size() - 1) % input.size()];


		float t = -(prev.position.y - prev.w) / ((curr.position.y - curr.w) - (prev.position.y - prev.w));
		if (!clipsUpPlane(prev) && !clipsUpPlane(curr)) {
			output.push_back(curr);
		}

		else if (!clipsUpPlane(prev) && clipsUpPlane(curr)) {
			//add the intersection
			Vertex intersection = interpolateVertex(prev, t, curr);
			output.push_back(intersection);
		}

		else if (clipsUpPlane(prev) && !clipsUpPlane(curr)) {
			//add intersection and curr
			Vertex intersection = interpolateVertex(prev, t, curr);
			output.push_back(intersection);
			output.push_back(curr);
		}

	}

}



void clipAgainstDownPlane(const std::vector<Vertex>& input, std::vector<Vertex>& output) {
	
	output.clear();
	
	for (int i = 0; i < input.size(); i++) {
		Vertex curr = input[i];
		Vertex prev = input[(i + input.size() - 1) % input.size()];


		float t = -(prev.position.y + prev.w) / ((curr.position.y + curr.w) - (prev.position.y + prev.w));
		if (!clipsDownPlane(prev) && !clipsDownPlane(curr)) {
			output.push_back(curr);
		}

		else if (!clipsDownPlane(prev) && clipsDownPlane(curr)) {
			//add the intersection
			Vertex intersection = interpolateVertex(prev, t, curr);
			output.push_back(intersection);
		}

		else if (clipsDownPlane(prev) && !clipsDownPlane(curr)) {
			//add intersection and curr
			Vertex intersection = interpolateVertex(prev, t, curr);
			output.push_back(intersection);
			output.push_back(curr);
		}

	}

}




void clipAgainstFarPlane(const std::vector<Vertex>& input, std::vector<Vertex>& output) {

	output.clear();

	for (int i = 0; i < input.size(); i++) {
		Vertex curr = input[i];
		Vertex prev = input[(i + input.size() - 1) % input.size()];


		float t = -(prev.position.z - prev.w) / ((curr.position.z - curr.w) - (prev.position.z - prev.w));
		if (!clipsFarPlane(prev) && !clipsFarPlane(curr)) {
			output.push_back(curr);
		}

		else if (!clipsFarPlane(prev) && clipsFarPlane(curr)) {
			//add the intersection
			Vertex intersection = interpolateVertex(prev, t, curr);
			output.push_back(intersection);
		}

		else if (clipsFarPlane(prev) && !clipsFarPlane(curr)) {
			//add intersection and curr
			Vertex intersection = interpolateVertex(prev, t, curr);
			output.push_back(intersection);
			output.push_back(curr);
		}

	}

}


void clipAgainstNearPlane(const std::vector<Vertex>& input, std::vector<Vertex>& output) {
	
	output.clear();
	
	for (int i = 0; i < input.size(); i++) {
		Vertex curr = input[i];
		Vertex prev = input[(i + input.size() - 1) % input.size()];


		float t = -(prev.position.z + prev.w) / ((curr.position.z + curr.w) - (prev.position.z + prev.w));
		if (!clipsNearPlane(prev) && !clipsNearPlane(curr)) {
			output.push_back(curr);
		}

		else if (!clipsNearPlane(prev) && clipsNearPlane(curr)) {
			//add the intersection
			Vertex intersection = interpolateVertex(prev, t, curr);
			output.push_back(intersection);
		}

		else if (clipsNearPlane(prev) && !clipsNearPlane(curr)) {
			//add intersection and curr
			Vertex intersection = interpolateVertex(prev, t, curr);
			output.push_back(intersection);
			output.push_back(curr);
		}

	}

}