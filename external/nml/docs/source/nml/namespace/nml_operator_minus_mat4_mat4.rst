:orphan:

nml::mat4 operator-(nml::mat4 lhs, const nml::mat4& rhs)
========================================================

Return a *mat4* that is the difference between two *mat4*.

The difference between two *mat4* is calculated this way:

:math:`\begin{bmatrix} lhs.x.x & lhs.y.x & lhs.z.x & lhs.x.x \\ lhs.x.y & lhs.y.y & lhs.z.y & lhs.x.y \\ lhs.x.z & lhs.y.z & lhs.z.z & lhs.x.z \\ lhs.x.w & lhs.y.w & lhs.z.w & lhs.w.w \end{bmatrix} - \begin{bmatrix} rhs.x.x & rhs.y.x & rhs.z.x & rhs.w.x \\ rhs.x.y & rhs.y.y & rhs.z.y & rhs.w.y \\ rhs.x.z & rhs.y.z & rhs.z.z & rhs.w.z \\ rhs.x.w & rhs.y.w & rhs.z.w & rhs.w.w \end{bmatrix} =`

:math:`\begin{bmatrix} lhs.x.x - rhs.x.x & lhs.y.x - rhs.y.x & lhs.z.x - rhs.z.x & lhs.x.x - rhs.w.x \\ lhs.x.y - rhs.x.y & lhs.y.y - rhs.y.y & lhs.z.y - rhs.z.y & lhs.x.y - rhs.w.y \\ lhs.x.z - rhs.x.z & lhs.y.z - rhs.y.z & lhs.z.z - rhs.z.z & lhs.x.z - rhs.w.z \\ lhs.x.w - rhs.x.w & lhs.y.w - rhs.y.w & lhs.z.w - rhs.z.w & lhs.w.w - rhs.w.w \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat4.h"
	#include <iostream>

	int main() {
		nml::mat4 a(2.0f, 5.0f, 3.0f, 6.0f, 8.0f, 2.0f, 4.0f, 1.5f, 9.0f, 3.25f, 4.99f, 1.0f, 2.0f, 5.5f, 4.2f, 2.0f);
		nml::mat4 b(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
		nml::mat4 c = a - b;
		std::cout << nml::to_string(c) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[1.000000, 3.000000, 0.000000, 2.000000], [3.000000, -4.000000, -3.000000, -6.500000], [0.000000, -6.750000, -6.010000, -11.000000], [-11.000000, -8.500000, -10.800000, -14.000000]]