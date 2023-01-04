:orphan:

nml::mat3 operator*(nml::mat3 lhs, const nml::mat3& rhs)
========================================================

Return a *mat3* that is the product between two *mat3*.

The product between two *mat3* is calculated this way:

:math:`\begin{bmatrix} lhs.x.x & lhs.y.x & lhs.z.x \\ lhs.x.y & lhs.y.y & lhs.z.y \\ lhs.x.z & lhs.y.z & lhs.z.z \end{bmatrix} * \begin{bmatrix} rhs.x.x & rhs.y.x & rhs.z.x \\ rhs.x.y & rhs.y.y & rhs.z.y \\ rhs.x.z & rhs.y.z & rhs.z.z \end{bmatrix} =`

:math:`\tiny \begin{bmatrix} lhs.x.x * rhs.x.x + lhs.y.x * rhs.x.y + lhs.z.x * rhs.x.z & lhs.x.x * rhs.y.x + lhs.y.x * rhs.y.y + lhs.z.x * rhs.y.z & lhs.x.x * rhs.z.x + lhs.y.x * rhs.z.y + lhs.z.x * rhs.z.z \\ lhs.x.y * rhs.x.x + lhs.y.y * rhs.x.y + lhs.z.y * rhs.x.z & lhs.x.y * rhs.y.x + lhs.y.y * rhs.y.y + lhs.z.y * rhs.y.z & lhs.x.y * rhs.z.x + lhs.y.y * rhs.z.y + lhs.z.y * rhs.z.z \\ lhs.x.z * rhs.x.x + lhs.y.z * rhs.x.y + lhs.z.z * rhs.x.z & lhs.x.z * rhs.y.x + lhs.y.z * rhs.y.y + lhs.z.z * rhs.y.z & lhs.x.z * rhs.z.x + lhs.y.z * rhs.z.y + lhs.z.z * rhs.z.z \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat3.h"
	#include <iostream>

	int main() {
		nml::mat3 a(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 10.0f);
		nml::mat3 b = nml::inverse(a);
		nml::mat3 c = a * b;
		std::cout << nml::to_string(c) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[1.000000, 0.000000, 0.000000], [0.000000, 1.000000, 0.000000], [0.000000, 0.000000, 1.000000]]