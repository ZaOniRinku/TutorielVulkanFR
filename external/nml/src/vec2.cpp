#include "../include/vec2.h"
#include <cmath>
#include <stdexcept>

namespace nml {

vec2::vec2(): x(0.0f), y(0.0f) {}
vec2::vec2(float _xy): x(_xy), y(_xy) {}
vec2::vec2(float _x, float _y): x(_x), y(_y) {}

vec2& vec2::operator+=(const vec2& other) { 
	x += other.x;
	y += other.y;

	return *this;
}

vec2& vec2::operator-=(const vec2& other) { 
	x -= other.x;
	y -= other.y;

	return *this;
}

vec2& vec2::operator*=(const float other) {
	x *= other;
	y *= other;

	return *this;
}

vec2& vec2::operator/=(const float other) {
	x /= other;
	y /= other;

	return *this;
}

float& vec2::operator[](size_t index) {
	if (index == 0) { return x; }
	else if (index == 1) { return y; }
	else { throw std::out_of_range("vec2::operator[]: index is out of range."); }
}

const float vec2::operator[](size_t index) const {
	if (index == 0) { return x; }
	else if (index == 1) { return y; }
	else { throw std::out_of_range("vec2::operator[]: index is out of range."); }
}

float vec2::length() const {
	return std::sqrt((x * x) + (y * y));
}

float* vec2::data() {
	return &x;
}

vec2 operator+(vec2 lhs, const vec2& rhs) { 
	lhs += rhs;

	return lhs;
}

vec2 operator-(vec2 lhs, const vec2& rhs) {
	lhs -= rhs;

	return lhs;
}

vec2 operator*(vec2 lhs, const float rhs) {
	lhs *= rhs;

	return lhs;
}

vec2 operator*(float lhs, const vec2& rhs) {
	return (rhs * lhs);
}

vec2 operator/(vec2 lhs, const float rhs) { 
	lhs /= rhs;

	return lhs;
}

bool operator==(const vec2& lhs, const vec2& rhs) {
	return ((lhs.x == rhs.x) && (lhs.y == rhs.y));
}

bool operator!=(const vec2& lhs, const vec2& rhs) {
	return !(lhs == rhs);
}

vec2 normalize(const vec2& vec) {
	const float l = vec.length();

	return (vec / l);
}

float dot(const vec2& a, const vec2& b) {
	return ((a.x * b.x) + (a.y * b.y));
}

vec2 reflect(const vec2& i, const vec2& n) {
	return (i - 2.0f * dot(n, i) * n);
}

vec2 refract(const vec2& i, const vec2& n, float ior) {
	const float ndoti = dot(n, i);
	const float k = 1.0f - ior * ior * (1.0f - ndoti * ndoti);
	if (k < 0.0f) {
		return vec2(0.0f);
	}
	else {
		return ior * i - (ior * ndoti + std::sqrt(k)) * n;
	}
}

std::string to_string(const vec2& vec) {
	return ("[" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + "]");
}

}