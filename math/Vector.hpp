#pragma once
#include <cmath>


template<typename T>
struct Vector2 {
	T x, y;

	Vector2() : x(0), y(0) {}
	Vector2(T valX, T valY) : x(valX), y(valY) {}

	//Some Operations

	Vector2 operator+(const Vector2& other) const {
		return { x + other.x, y + other.y };
	}

	Vector2 operator-(const Vector2& other) const {
		return { x - other.x, y - other.y };
	}

	Vector2 operator*(const T other) const {
		return { x * other, y * other };
	}



	T dot(const Vector2& other) const {
		return x * other.x + y * other.y;
	}

};


using Vector2f = Vector2<float>;





template<typename T>
struct Vector3 {
	T x, y, z;

	
	static const Vector3<T> up;
	static const Vector3<T> right;
	static const Vector3<T> forward;
	
	Vector3() : x(0), y(0), z(0) {}
	Vector3(T valX, T valY, T valZ) : x(valX), y(valY), z(valZ) {}




	//Some operator overloads

	Vector3 operator+(const Vector3& other) const {
		return { x + other.x, y + other.y, z + other.z };
	}

	Vector3 operator-(const Vector3& other) const {
		return { x - other.x, y - other.y, z - other.z };
	}

	//Scalar Multiplication
	Vector3 operator*(const T other) const {
		return { x * other, y * other, z * other };
	}




	//Some methods

	T dot(const Vector3& other) const {
		return x * other.x + y * other.y + z * other.z;
	}

	Vector3 cross(const Vector3& other) const {
		return { y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x };
	}
	
	static Vector3 normalize(const Vector3& vec) {
		T magnitude = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
		return {
			vec.x / magnitude,
			vec.y / magnitude,
			vec.z / magnitude
		};
	}

};

using Vector3f = Vector3<float>;
using Vector3i = Vector3<int>;

template<typename T>
const Vector3<T> Vector3<T>::up = Vector3<T>(0, 1, 0);
template<typename T>
const Vector3<T> Vector3<T>::right = Vector3<T>(1, 0, 0);
template<typename T>
const Vector3<T> Vector3<T>::forward = Vector3<T>(0, 0, 1);





template<typename T>
struct Vector4 {
	T w, x, y, z;

	Vector4() : w(0), x(0), y(0), z(0) {}
	Vector4(T w, T x, T y, T z) : w(w), x(x), y(y), z(z) {}

};





using Vector4f = Vector4<float>;