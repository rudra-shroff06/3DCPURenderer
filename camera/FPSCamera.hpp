#pragma once
#include "camera.hpp"





struct FPSCamera : public Camera {
	
	
	FPSCamera();
	FPSCamera(const Vector3f& eye);
	
	void yaw(float angle);
	void pitch(float angle);

};