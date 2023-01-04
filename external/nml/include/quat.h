#pragma once
#include <string>

namespace nml {

struct vec3;

// a + bi + cj + dk
struct quat {
    float a;
    float b;
    float c;
    float d;

    // Constructors
    quat();
    quat(float _a, float _b, float _c, float _d);

    // Operators
    quat& operator+=(const quat& other);
    quat& operator-=(const quat& other);
    quat& operator*=(const quat& other);
    quat& operator*=(const float other);
	quat& operator/=(const float other);
    float& operator[](size_t index);
	const float operator[](size_t index) const;

    // Functions
    float length() const;

    float* data();
};

// Operators
quat operator+(quat lhs, const quat& rhs);
quat operator-(quat lhs, const quat& rhs);
quat operator*(quat lhs, const quat& rhs);
quat operator*(quat lhs, const float rhs);
quat operator*(float lhs, const quat& rhs);
quat operator/(quat lhs, const float rhs);
bool operator==(const quat& lhs, const quat& rhs);
bool operator!=(const quat& lhs, const quat& rhs);

// Functions
quat conjugate(const quat& qua);
quat normalize(const quat& qua);

quat to_quat(const vec3& vec);
std::string to_string(const quat& qua);

}