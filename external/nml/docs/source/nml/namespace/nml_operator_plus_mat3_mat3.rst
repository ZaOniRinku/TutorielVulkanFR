:orphan:

nml::mat3 operator+(nml::mat3 lhs, const nml::mat3& rhs)
========================================================

Return a *mat3* that is the sum between two *mat3*.

The sum between two *mat3* is calculated this way:

:math:`\begin{bmatrix} lhs.x.x & lhs.y.x & lhs.z.x \\ lhs.x.y & lhs.y.y & lhs.z.y \\ lhs.x.z & lhs.y.z & lhs.z.z \end{bmatrix} + \begin{bmatrix} rhs.x.x & rhs.y.x & rhs.z.x \\ rhs.x.y & rhs.y.y & rhs.z.y \\ rhs.x.z & rhs.y.z & rhs.z.z \end{bmatrix} =`

:math:`\begin{bmatrix} lhs.x.x + rhs.x.x & lhs.y.x + rhs.y.x & lhs.z.x + rhs.z.x \\ lhs.x.y + rhs.x.y & lhs.y.y + rhs.y.y & lhs.z.y + rhs.z.y \\ lhs.x.z + rhs.x.z & lhs.y.z + rhs.y.z & lhs.z.z + rhs.z.z \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat3.h"
	#include <iostream>

	int main() {
		nml::mat3 a(1.0f, 2.0f, 4.0f, 8.0f, 16.0f, 32.0f, 64.0f, 128.0f, 256.0f);
		nml::mat3 b(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f);
		nml::mat3 c = a + b;
		std::cout << nml::to_string(c) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[3.000000, 6.000000, 10.000000], [16.000000, 26.000000, 44.000000], [78.000000, 144.000000, 274.000000]]