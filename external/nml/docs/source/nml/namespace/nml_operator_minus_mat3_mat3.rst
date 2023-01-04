:orphan:

nml::mat3 operator-(nml::mat3 lhs, const nml::mat3& rhs)
========================================================

Return a *mat3* that is the difference between two *mat3*.

The difference between two *mat3* is calculated this way:

:math:`\begin{bmatrix} lhs.x.x & lhs.y.x & lhs.z.x \\ lhs.x.y & lhs.y.y & lhs.z.y \\ lhs.x.z & lhs.y.z & lhs.z.z \end{bmatrix} - \begin{bmatrix} rhs.x.x & rhs.y.x & rhs.z.x \\ rhs.x.y & rhs.y.y & rhs.z.y \\ rhs.x.z & rhs.y.z & rhs.z.z \end{bmatrix} =`

:math:`\begin{bmatrix} lhs.x.x - rhs.x.x & lhs.y.x - rhs.y.x & lhs.z.x - rhs.z.x \\ lhs.x.y - rhs.x.y & lhs.y.y - rhs.y.y & lhs.z.y - rhs.z.y \\ lhs.x.z - rhs.x.z & lhs.y.z - rhs.y.z & lhs.z.z - rhs.z.z \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat3.h"
	#include <iostream>

	int main() {
		nml::mat3 a(2.0f, 5.0f, 3.0f, 6.0f, 8.0f, 2.0f, 4.0f, 1.5f, 9.0f);
		nml::mat3 b(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
		nml::mat3 c = a - b;
		std::cout << nml::to_string(c) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[1.000000, 3.000000, 0.000000], [2.000000, 3.000000, -4.000000], [-3.000000, -6.500000, 0.000000]]