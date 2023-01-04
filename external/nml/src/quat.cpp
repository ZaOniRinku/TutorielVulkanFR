#include "../include/quat.h"
#include "../include/vec3.h"
#include <cmath>
#include <stdexcept>

namespace nml {

quat::quat(): a(1.0f), b(0.0f), c(0.0f), d(0.0f) {}
quat::quat(float _a, float _b, float _c, float _d): a(_a), b(_b), c(_c), d(_d) {}

quat& quat::operator+=(const quat& other) {
	a += other.a;
	b += other.b;
	c += other.c;
	d += other.d;

	return *this;
}

quat& quat::operator-=(const quat& other) {
	a -= other.a;
	b -= other.b;
	c -= other.c;
	d -= other.d;

	return *this;
}

quat& quat::operator*=(const quat& other) {
	const quat tmp((a * other.a) - (b * other.b) - (c * other.c) - (d * other.d),
	(a * other.b) + (b * other.a) + (c * other.d) - (d * other.c),
	(a * other.c) - (b * other.d) + (c * other.a) + (d * other.b),
	(a * other.d) + (b * other.c) - (c * other.b) + (d * other.a));

	a = tmp.a;
	b = tmp.b;
	c = tmp.c;
	d = tmp.d;

	return *this;
}

quat& quat::operator*=(const float other) {
	a *= other;
	b *= other;
	c *= other;
	d *= other;

	return *this;
}

quat& quat::operator/=(const float other) {
	a /= other;
	b /= other;
	c /= other;
	d /= other;

	return *this;
}

float& quat::operator[](size_t index) {
	if (index == 0) { return a; }
	else if (index == 1) { return b; }
	else if (index == 2) { return c; }
	else if (index == 3) { return d; }
	else { throw std::out_of_range("quat::operator[]: index is out of range."); }
}

const float quat::operator[](size_t index) const {
	if (index == 0) { return a; }
	else if (index == 1) { return b; }
	else if (index == 2) { return c; }
	else if (index == 3) { return d; }
	else { throw std::out_of_range("quat::operator[]: index is out of range."); }
}

float quat::length() const {
	return std::sqrt((a * a) + (b * b) + (c * c) + (d * d));
}

float* quat::data() {
	return &a;
}

quat operator+(quat lhs, const quat& rhs) {
	lhs += rhs;

	return lhs;
}

quat operator-(quat lhs, const quat& rhs) {
	lhs -= rhs;

	return lhs;
}

quat operator*(quat lhs, const quat& rhs) {
	lhs *= rhs;

	return lhs;
}

quat operator*(quat lhs, const float rhs) {
	lhs *= rhs;

	return lhs;
}

quat operator*(float lhs, const quat& rhs) {
	return (rhs * lhs);
}

quat operator/(quat lhs, const float rhs) {
	lhs /= rhs;

	return lhs;
}

bool operator==(const quat& lhs, const quat& rhs) {
	return ((lhs.a == rhs.a) && (lhs.b == rhs.b) && (lhs.c == rhs.c) && (lhs.d == rhs.d));
}

bool operator!=(const quat& lhs, const quat& rhs) {
	return !(lhs == rhs);
}

quat conjugate(const quat& qua) {
	return quat(qua.a, -qua.b, -qua.c, -qua.d);
}

quat normalize(const quat& qua) {
	const float l = qua.length();

	return (qua / l);
}

quat to_quat(const vec3& vec) {
	const float cosHalfPhi = std::cos(vec.x / 2.0f);
	const float sinHalfPhi = std::sin(vec.x / 2.0f);
	const float cosHalfTheta = std::cos(vec.y / 2.0f);
	const float sinHalfTheta = std::sin(vec.y / 2.0f);
	const float cosHalfPsi = std::cos(vec.z / 2.0f);
	const float sinHalfPsi = std::sin(vec.z / 2.0f);

	return quat(cosHalfPhi * cosHalfTheta * cosHalfPsi + sinHalfPhi * sinHalfTheta * sinHalfPsi,
		sinHalfPhi * cosHalfTheta * cosHalfPsi - cosHalfPhi * sinHalfTheta * sinHalfPsi,
		cosHalfPhi * sinHalfTheta * cosHalfPsi + sinHalfPhi * cosHalfTheta * sinHalfPsi,
		cosHalfPhi * cosHalfTheta * sinHalfPsi - sinHalfPhi * sinHalfTheta * cosHalfPsi);
}

std::string to_string(const quat& qua) {
	return std::to_string(qua.a) + " + " + std::to_string(qua.b) + "i + " + std::to_string(qua.c) + "j + " + std::to_string(qua.d) + "k";
}

}