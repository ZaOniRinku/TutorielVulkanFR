:orphan:

nml::mat4 operator/(nml::mat4 lhs, const float rhs)
===================================================

Return a *mat4* that is the quotient between a *mat4* and a scalar.

The quotient between a *mat4* and a scalar is calculated this way:

:math:`\frac{\begin{bmatrix} lhs.x.x & lhs.y.x & lhs.z.x & lhs.w.x \\ lhs.x.y & lhs.y.y & lhs.z.y & lhs.w.y \\ lhs.x.z & lhs.y.z & lhs.z.z & lhs.w.z \\ lhs.x.w & lhs.y.w & lhs.z.w & lhs.w.w \end{bmatrix}}{rhs} = \begin{bmatrix} \frac{lhs.x.x}{rhs} & \frac{lhs.y.x}{rhs} & \frac{lhs.z.x}{rhs} & \frac{lhs.w.x}{rhs} \\ \frac{lhs.x.y}{rhs} & \frac{lhs.y.y}{rhs} & \frac{lhs.z.y}{rhs} & \frac{lhs.w.y}{rhs} \\ \frac{lhs.x.w}{rhs} & \frac{lhs.y.z}{rhs} & \frac{lhs.z.z}{rhs} & \frac{lhs.w.z}{rhs} \\ \frac{lhs.x.w}{rhs} & \frac{lhs.y.w}{rhs} & \frac{lhs.z.w}{rhs} & \frac{lhs.w.w}{rhs} \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat4.h"
	#include <iostream>

	int main() {
		nml::mat4 a(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
		nml::mat4 b = a / 2.0f;
		std::cout << nml::to_string(b) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[0.500000, 1.000000, 1.500000, 2.000000], [2.500000, 3.000000, 3.500000, 4.000000], [4.500000, 5.000000, 5.500000, 6.000000], [6.500000, 7.000000, 7.500000, 8.000000]]