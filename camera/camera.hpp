#pragma once
#include <cmath>
#include "../math/Vector.hpp"
#include "../math/Quaternion.hpp"



struct Camera {
	Vector3f eye;
	Vector3f forward;
	Vector3f up;
	Vector3f right;
	Quaternion rotation;
	float far;
	float near;
	float fov;
	float aspect;


	Vector3f applyView(const Vector3f& p) const {
		const Vector3f pos = p - eye;
		Quaternion rotUpQ = this->rotation * this->up * this->rotation.inverse();
		Quaternion rotForwardQ = this->rotation * this->forward * this->rotation.inverse();
		
		Vector3f rotUp = rotUpQ.getVectorPart();
		const Vector3f rotForward = Vector3f(0, 0, 0) - rotForwardQ.getVectorPart();
		const Vector3f rotRight = Vector3f::normalize(rotForward.cross(rotUp));
		rotUp = Vector3f::normalize(rotRight.cross(rotForward));


		return {
			rotRight.dot(pos),
			rotUp.dot(pos),
			rotForward.dot(pos)
		};

	}


	Vector4f applyProjection(const Vector3f& p) const {
		float fovTan = tan(this->fov / 2);

		return {

			-p.z,

			p.x / (this->aspect * fovTan),
			
			p.y / fovTan,
			
			(((-this->far - this->near) * p.z) - (2 * this->far * this->near)) / (this->far - this->near)

		};
	}
};