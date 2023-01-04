#pragma once
#include <string>

namespace nml {

// x | y
struct vec2 {
	float x;
	float y;
	
	// Constructors
	vec2();
	vec2(float _xy);
	vec2(float _x, float _y);

	// Operators
	vec2& operator+=(const vec2& other);
	vec2& operator-=(const vec2& other);
	vec2& operator*=(const float other);
	vec2& operator/=(const float other);
	float& operator[](size_t index);
	const float operator[](size_t index) const;

	// Functions
	float length() const;

	float* data();
};

// Operators
vec2 operator+(vec2 lhs, const vec2& rhs);
vec2 operator-(vec2 lhs, const vec2& rhs);
vec2 operator*(vec2 lhs, const float rhs);
vec2 operator*(float lhs, const vec2& rhs);
vec2 operator/(vec2 lhs, const float rhs);
bool operator==(const vec2& lhs, const vec2& rhs);
bool operator!=(const vec2& lhs, const vec2& rhs);

// Functions
vec2 normalize(const vec2& vec);
float dot(const vec2& a, const vec2& b);
vec2 reflect(const vec2& i, const vec2& n);
vec2 refract(const vec2& i, const vec2& n, float ior);

std::string to_string(const vec2& vec);

}