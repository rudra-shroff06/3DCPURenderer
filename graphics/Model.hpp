#pragma once
#include "../math/Vector.hpp"
#include "Mesh.hpp"
#include "../math/Transform.hpp"




struct Model {
	Mesh mMesh;
	Transform transform;

	Model() = default;
};



