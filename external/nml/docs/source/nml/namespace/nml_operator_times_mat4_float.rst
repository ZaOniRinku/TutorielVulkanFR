:orphan:

nml::mat4 operator*(nml::mat4 lhs, const float rhs)
===================================================

Return a *mat4* that is the product between a *mat4* and a scalar.

The product between a *mat4* and a scalar is calculated this way:

:math:`\begin{bmatrix} lhs.x.x & lhs.y.x & lhs.z.x & lhs.w.x \\ lhs.x.y & lhs.y.y & lhs.z.y & lhs.w.y \\ lhs.x.z & lhs.y.z & lhs.z.z & lhs.w.z \\ lhs.x.w & lhs.y.w & lhs.z.w & lhs.w.w \end{bmatrix} * rhs =`

:math:`\begin{bmatrix} lhs.x.x * rhs & lhs.y.x * rhs & lhs.z.x * rhs & lhs.w.x * rhs \\ lhs.x.y * rhs & lhs.y.y * rhs & lhs.z.y * rhs & lhs.w.y * rhs \\ lhs.x.z * rhs & lhs.y.z * rhs & lhs.z.z * rhs & lhs.w.z * rhs \\ lhs.x.w * rhs & lhs.y.w * rhs & lhs.z.w * rhs & lhs.w.w * rhs \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat4.h"
	#include <iostream>

	int main() {
		nml::mat4 a(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
		nml::mat4 b = a * 3.0f;
		std::cout << nml::to_string(b) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[3.000000, 6.000000, 9.000000, 12.000000], [15.000000, 18.000000, 21.000000, 24.000000], [27.000000, 30.000000, 33.000000, 36.000000], [39.000000, 42.000000, 45.000000, 48.000000]]