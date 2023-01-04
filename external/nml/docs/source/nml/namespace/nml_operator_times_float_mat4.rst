:orphan:

nml::mat4 operator*(float lhs, const nml::mat4& rhs)
====================================================

Return a *mat4* that is the product between a scalar and a *mat4*.

The product between a scalar and a *mat4* is calculated this way:

:math:`lhs * \begin{bmatrix} rhs.x.x & rhs.y.x & rhs.z.x & rhs.w.x \\ rhs.x.y & rhs.y.y & rhs.z.y & rhs.w.y \\ rhs.x.z & rhs.y.z & rhs.z.z & rhs.w.z \\ rhs.x.w & rhs.y.w & rhs.z.w & rhs.w.w \end{bmatrix} =`

:math:`\begin{bmatrix} lhs * rhs.x.x & lhs * rhs.y.x & lhs * rhs.z.x & lhs * rhs.w.x \\ lhs * rhs.x.y & lhs * rhs.y.y & lhs * rhs.z.y & lhs * rhs.w.y \\ lhs * rhs.x.z & lhs * rhs.y.z & lhs * rhs.z.z & lhs * rhs.w.z \\ lhs * rhs.x.w & lhs * rhs.y.w & lhs * rhs.z.w & lhs * rhs.w.w \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat4.h"
	#include <iostream>

	int main() {
		nml::mat4 a(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
		nml::mat4 b = 3.0f * a;
		std::cout << nml::to_string(b) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[3.000000, 6.000000, 9.000000, 12.000000], [15.000000, 18.000000, 21.000000, 24.000000], [27.000000, 30.000000, 33.000000, 36.000000], [39.000000, 42.000000, 45.000000, 48.000000]]