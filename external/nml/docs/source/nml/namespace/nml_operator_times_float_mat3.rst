:orphan:

nml::mat3 operator*(float lhs, const nml::mat3& rhs)
====================================================

Return a *mat3* that is the product between a scalar and a *mat3*.

The product between a scalar and a *mat3* is calculated this way:

:math:`lhs * \begin{bmatrix} rhs.x.x & rhs.y.x & rhs.z.x \\ rhs.x.y & rhs.y.y & rhs.z.y \\ rhs.x.z & rhs.y.z & rhs.z.z \end{bmatrix} = \begin{bmatrix} lhs * rhs.x.x & lhs * rhs.y.x & lhs * rhs.z.x \\ lhs * rhs.x.y & lhs * rhs.y.y & lhs * rhs.z.y \\ lhs * rhs.x.z & lhs * rhs.y.z & lhs * rhs.z.z \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat3.h"
	#include <iostream>

	int main() {
		nml::mat3 a(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
		nml::mat3 b = 3.0f * a;
		std::cout << nml::to_string(b) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[3.000000, 6.000000, 9.000000], [12.000000, 15.000000, 18.000000], [21.000000, 24.000000, 27.000000]]