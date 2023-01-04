#include "../include/mat2.h"
#include "../include/vec2.h"
#include <stdexcept>

namespace nml {

mat2::mat2(): x(1.0f, 0.0f), y(0.0f, 1.0f) {}
mat2::mat2(float _xxxyyxyy): x(_xxxyyxyy), y(_xxxyyxyy) {}
mat2::mat2(float _xx, float _xy, float _yx, float _yy): x(_xx, _xy), y(_yx, _yy) {}
mat2::mat2(float _xx, float _xy, vec2 _yxyy): x(_xx, _xy), y(_yxyy) {}
mat2::mat2(vec2 _xxxy, float _yx, float _yy): x(_xxxy), y(_yx, _yy) {}
mat2::mat2(vec2 _xxxy, vec2 _yxyy): x(_xxxy), y(_yxyy) {}

mat2& mat2::operator+=(const mat2& other) {
	x += other.x;
	y += other.y;

	return *this;
}

mat2& mat2::operator-=(const mat2& other) {
	x -= other.x;
	y -= other.y;

	return *this;
}

mat2& mat2::operator*=(const mat2& other) {
	const mat2 tmp(vec2(x.x * other.x.x + y.x * other.x.y,
			x.y * other.x.x + y.y * other.x.y),
		vec2(x.x * other.y.x + y.x * other.y.y,
			x.y * other.y.x + y.y * other.y.y));

	x = tmp.x;
	y = tmp.y;

	return *this;
}

mat2& mat2::operator*=(const float other) {
	x *= other;
	y *= other;

	return *this;
}

mat2& mat2::operator/=(const float other) {
	x /= other;
	y /= other;

	return *this;
}

vec2& mat2::operator[](size_t index) {
	if (index == 0) { return x; }
	else if (index == 1) { return y; }
	else { throw std::out_of_range("mat2::operator[]: index is out of range."); }
}

const vec2& mat2::operator[](size_t index) const {
	if (index == 0) { return x; }
	else if (index == 1) { return y; }
	else { throw std::out_of_range("mat2::operator[]: index is out of range."); }
}

float mat2::det() const {
	return (x.x * y.y -
		y.x * x.y);
}

float* mat2::data() {
	return x.data();
}

mat2 operator+(mat2 lhs, const mat2& rhs) {
	lhs += rhs;

	return lhs;
}

mat2 operator-(mat2 lhs, const mat2& rhs) {
	lhs -= rhs;

	return lhs;
}

mat2 operator*(mat2 lhs, const mat2& rhs) { 
	lhs *= rhs;

	return lhs;
}

vec2 operator*(mat2 lhs, const vec2& rhs) {
	return vec2(lhs.x.x * rhs.x + lhs.y.x * rhs.y,
		lhs.x.y * rhs.x + lhs.y.y * rhs.y);
}

mat2 operator*(mat2 lhs, const float rhs) {
	lhs *= rhs;

	return lhs;
}

mat2 operator*(float lhs, const mat2& rhs) {
	return (rhs * lhs);
}

mat2 operator/(mat2 lhs, const float rhs) {
	lhs /= rhs;

	return lhs;
}

bool operator==(const mat2& lhs, const mat2& rhs) {
	return ((lhs.x == rhs.x) && (lhs.y == rhs.y));
}

bool operator!=(const mat2& lhs, const mat2& rhs) {
	return !(lhs == rhs);
}

mat2 transpose(const mat2& mat) {
	return mat2(mat.x.x, mat.y.x, mat.x.y, mat.y.y);
}

mat2 inverse(const mat2& mat) {
	const float determinant = mat.det();

	return ((1.0f / determinant) * mat2(mat.y.y, -mat.x.y, -mat.y.x, mat.x.x));
}

std::string to_string(const mat2& mat) {
	return ("[" + to_string(mat.x) + ", " + to_string(mat.y) + "]");
}

}