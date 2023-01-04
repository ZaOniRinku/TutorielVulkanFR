#include "../include/vec4.h"
#include "../include/vec2.h"
#include "../include/vec3.h"
#include <cmath>
#include <stdexcept>

namespace nml {

vec4::vec4(): x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
vec4::vec4(float _xyzw): x(_xyzw), y(_xyzw), z(_xyzw), w(_xyzw) {}
vec4::vec4(float _x, float _y, float _z, float _w): x(_x), y(_y), z(_z), w(_w) {}
vec4::vec4(float _x, vec3 _yzw): x(_x), y(_yzw.x), z(_yzw.y), w(_yzw.z) {}
vec4::vec4(vec3 _xyz, float _w): x(_xyz.x), y(_xyz.y), z(_xyz.z), w(_w) {}
vec4::vec4(float _x, float _y, vec2 _zw): x(_x), y(_y), z(_zw.x), w(_zw.y) {}
vec4::vec4(float _x, vec2 _yz, float _w): x(_x), y(_yz.x), z(_yz.y), w(_w) {}
vec4::vec4(vec2 _xy, float _z, float _w): x(_xy.x), y(_xy.y), z(_z), w(_w) {}
vec4::vec4(vec2 _xy, vec2 _zw): x(_xy.x), y(_xy.y), z(_zw.x), w(_zw.y) {}

vec4& vec4::operator+=(const vec4& other) { 
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;

	return *this;
}

vec4& vec4::operator-=(const vec4& other) { 
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;

	return *this;
}

vec4& vec4::operator*=(const float other) {
	x *= other;
	y *= other;
	z *= other;
	w *= other;

	return *this;
}

vec4& vec4::operator/=(const float other) {
	x /= other;
	y /= other;
	z /= other;
	w /= other;

	return *this;
}

float& vec4::operator[](size_t index) {
	if (index == 0) { return x; }
	else if (index == 1) { return y; }
	else if (index == 2) { return z; }
	else if (index == 3) { return w; }
	else { throw std::out_of_range("vec4::operator[]: index is out of range."); }
}

const float vec4::operator[](size_t index) const {
	if (index == 0) { return x; }
	else if (index == 1) { return y; }
	else if (index == 2) { return z; }
	else if (index == 3) { return w; }
	else { throw std::out_of_range("vec4::operator[]: index is out of range."); }
}

float vec4::length() const {
	return std::sqrt((x * x) + (y * y) + (z * z) + (w * w));
}

float* vec4::data() {
	return &x;
}

vec4 operator+(vec4 lhs, const vec4& rhs) { 
	lhs += rhs;

	return lhs;
}

vec4 operator-(vec4 lhs, const vec4& rhs) {
	lhs -= rhs;

	return lhs;
}

vec4 operator*(vec4 lhs, const float rhs) {
	lhs *= rhs;

	return lhs;
}

vec4 operator*(float lhs, const vec4& rhs) {
	return (rhs * lhs);
}

vec4 operator/(vec4 lhs, const float rhs) { 
	lhs /= rhs;

	return lhs;
}

bool operator==(const vec4& lhs, const vec4& rhs) {
	return ((lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z) && (lhs.w == rhs.w));
}

bool operator!=(const vec4& lhs, const vec4& rhs) {
	return !(lhs == rhs);
}

vec4 normalize(const vec4& vec) {
	const float l = vec.length();

	return (vec / l);
}

float dot(const vec4& a, const vec4& b) {
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w));
}

vec4 reflect(const vec4& i, const vec4& n) {
	return (i - 2.0f * dot(n, i) * n);
}

vec4 refract(const vec4& i, const vec4& n, float ior) {
	const float ndoti = dot(n, i);
	const float k = 1.0f - ior * ior * (1.0f - ndoti * ndoti);
	if (k < 0.0f) {
		return vec4(0.0f);
	}
	else {
		return ior * i - (ior * ndoti + std::sqrt(k)) * n;
	}
}

std::string to_string(const vec4& vec) {
	return ("[" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + ", " + std::to_string(vec.w) + "]");
}

}