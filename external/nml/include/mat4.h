#pragma once
#include "vec4.h"
#include <string>
#include <iostream>

namespace nml {

struct quat;

//  xx | yx | zx | wx
// ----|----|----|----
//  xy | yy | zy | wy
// ----|----|----|----
//  xz | yz | zz | wz
// ----|----|----|----
//  xw | yw | zw | ww
struct mat4 {
	vec4 x;
	vec4 y;
	vec4 z;
	vec4 w;
	
	// Constructors
	mat4();
	mat4(float _xxxyxzxwyxyyyzywzxzyzzzwwxwywzww);
	mat4(float _xx, float _xy, float _xz, float _xw, float _yx, float _yy, float _yz, float _yw, float _zx, float _zy, float _zz, float _zw, float _wx, float _wy, float _wz, float _ww);
	mat4(float _xx, float _xy, float _xz, float _xw, float _yx, float _yy, float _yz, float _yw, float _zx, float _zy, float _zz, float _zw, vec4 _wxwywzww);
	mat4(float _xx, float _xy, float _xz, float _xw, float _yx, float _yy, float _yz, float _yw, vec4 _zxzyzzzw, float _wx, float _wy, float _wz, float _ww);
	mat4(float _xx, float _xy, float _xz, float _xw, vec4 _yxyyyzyw, float _zx, float _zy, float _zz, float _zw, float _wx, float _wy, float _wz, float _ww);
	mat4(vec4 _xxxyxzxw, float _yx, float _yy, float _yz, float _yw, float _zx, float _zy, float _zz, float _zw, float _wx, float _wy, float _wz, float _ww);
	mat4(float _xx, float _xy, float _xz, float _xw, float _yx, float _yy, float _yz, float _yw, vec4 _zxzyzzzw, vec4 _wxwywzww);
	mat4(float _xx, float _xy, float _xz, float _xw, vec4 _yxyyyzyw, float _zx, float _zy, float _zz, float _zw, vec4 _wxwywzww);
	mat4(vec4 _xxxyxzxw, float _yx, float _yy, float _yz, float _yw, float _zx, float _zy, float _zz, float _zw, vec4 _wxwywzww);
	mat4(float _xx, float _xy, float _xz, float _xw, vec4 _yxyyyzyw, vec4 _zxzyzzzw, float _wx, float _wy, float _wz, float _ww);
	mat4(vec4 _xxxyxzxw, float _yx, float _yy, float _yz, float _yw, vec4 _zxzyzzzw, float _wx, float _wy, float _wz, float _ww);
	mat4(vec4 _xxxyxzxw, vec4 _yxyyyzyw, float _zx, float _zy, float _zz, float _zw, float _wx, float _wy, float _wz, float _ww);
	mat4(float _xx, float _xy, float _xz, float _xw, vec4 _yxyyyzyw, vec4 _zxzyzzzw, vec4 _wxwywzww);
	mat4(vec4 _xxxyxzxw, float _yx, float _yy, float _yz, float _yw, vec4 _zxzyzzzw, vec4 _wxwywzww);
	mat4(vec4 _xxxyxzxw, vec4 _yxyyyzyw, float _zx, float _zy, float _zz, float _zw, vec4 _wxwywzww);
	mat4(vec4 _xxxyxzxw, vec4 _yxyyyzyw, vec4 _zxzyzzzw, float _wx, float _wy, float _wz, float _ww);
	mat4(vec4 _xxxyxzxw, vec4 _yxyyyzyw, vec4 _zxzyzzzw, vec4 _wxwywzww);

	// Operators
	mat4& operator+=(const mat4& other);
	mat4& operator-=(const mat4& other);
	mat4& operator*=(const mat4& other);
	mat4& operator*=(const float other);
	mat4& operator/=(const float other);
	vec4& operator[](size_t index);
	const vec4& operator[](size_t index) const;

	// Functions
	float det() const;

	float* data();
};

// Operators
mat4 operator+(mat4 lhs, const mat4& rhs);
mat4 operator-(mat4 lhs, const mat4& rhs);
mat4 operator*(mat4 lhs, const mat4& rhs);
vec4 operator*(mat4 lhs, const vec4& rhs);
mat4 operator*(mat4 lhs, const float rhs);
mat4 operator*(float lhs, const mat4& rhs);
mat4 operator/(mat4 lhs, const float rhs);
bool operator==(const mat4& lhs, const mat4& rhs);
bool operator!=(const mat4& lhs, const mat4& rhs);

// Functions
mat4 transpose(const mat4& mat);
mat4 inverse(const mat4& mat);
mat4 translate(const vec3& translation);
mat4 rotate(const float angle, const vec3& axis);
mat4 scale(const vec3& scaling);
mat4 lookAtLH(const vec3& position, const vec3& to, const vec3& up);
mat4 lookAtRH(const vec3& position, const vec3& to, const vec3& up);
mat4 orthoLH(const float left, const float right, const float bottom, const float top, const float near, const float far);
mat4 orthoRH(const float left, const float right, const float bottom, const float top, const float near, const float far);
mat4 perspectiveLH(const float fovY, const float aspectRatio, const float near, const float far);
mat4 perspectiveRH(const float fovY, const float aspectRatio, const float near, const float far);

mat4 to_mat4(const quat& qua);
std::string to_string(const mat4& mat);

}