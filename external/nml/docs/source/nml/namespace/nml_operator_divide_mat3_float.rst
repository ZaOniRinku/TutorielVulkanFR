:orphan:

nml::mat3 operator/(nml::mat3 lhs, const float rhs)
===================================================

Return a *mat3* that is the quotient between a *mat3* and a scalar.

The quotient between a *mat3* and a scalar is calculated this way:

:math:`\frac{\begin{bmatrix} lhs.x.x & lhs.y.x & lhs.z.x \\ lhs.x.y & lhs.y.y & lhs.z.y \\ lhs.x.z & lhs.y.z & lhs.z.z \end{bmatrix}}{rhs} = \begin{bmatrix} \frac{lhs.x.x}{rhs} & \frac{lhs.y.x}{rhs} & \frac{lhs.z.x}{rhs} \\ \frac{lhs.x.y}{rhs} & \frac{lhs.y.y}{rhs} & \frac{lhs.z.y}{rhs} \\ \frac{lhs.x.z}{rhs} & \frac{lhs.y.z}{rhs} & \frac{lhs.z.z}{rhs} \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat3.h"
	#include <iostream>

	int main() {
		nml::mat3 a(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
		nml::mat3 b = a / 2.0f;
		std::cout << nml::to_string(b) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[0.500000, 1.000000, 1.500000], [2.000000, 2.500000, 3.000000], [3.500000, 4.000000, 4.500000]]