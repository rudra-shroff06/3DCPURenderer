#include "FPSCamera.hpp"





FPSCamera::FPSCamera() {
	this->eye = { 0, 0, 0 };
	this->forward = { 0, 0, -1 };
	this->up = { 0, 1, 0 };
	this->right = { 1, 0, 0 };
	this->rotation = { 1, 0, 0, 0 };
}


FPSCamera::FPSCamera(const Vector3f& eye) {
	this->eye = eye;
	this->forward = { 0, 0, -1 };
	this->up = { 0, 1, 0 };
	this->right = { 1, 0, 0 };
	this->rotation = { 1, 0, 0, 0 };
}


//Yaw in FPS Camera is rotate around global up
void FPSCamera::yaw(float angle) {
	float cosX = cos(angle / 2), sinX = sin(angle / 2);
	Quaternion q(cosX, Vector3f::up * sinX);
	this->rotation = q * this->rotation;
}



//Pitch in FPS Camera is rotate aorund its own local right vector
void FPSCamera::pitch(float angle) {
	float cosX = cos(angle / 2), sinX = sin(angle / 2);
	Quaternion q(cosX, this->right * sinX);
	this->rotation = this->rotation * q;
}