:orphan:

nml::mat3 operator*(nml::mat3 lhs, const float rhs)
===================================================

Return a *mat3* that is the product between a *mat3* and a scalar.

The product between a *mat3* and a scalar is calculated this way:

:math:`\begin{bmatrix} lhs.x.x & lhs.y.x & lhs.z.x \\ lhs.x.y & lhs.y.y & lhs.z.y \\ lhs.x.z & lhs.y.z & lhs.z.z \end{bmatrix} * rhs = \begin{bmatrix} lhs.x.x * rhs & lhs.y.x * rhs & lhs.z.x * rhs \\ lhs.x.y * rhs & lhs.y.y * rhs & lhs.z.y * rhs \\ lhs.x.z * rhs & lhs.y.z * rhs & lhs.z.z * rhs \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat3.h"
	#include <iostream>

	int main() {
		nml::mat3 a(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
		nml::mat3 b = a * 3.0f;
		std::cout << nml::to_string(b) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[3.000000, 6.000000, 9.000000], [12.000000, 15.000000, 18.000000], [21.000000, 24.000000, 27.000000]]