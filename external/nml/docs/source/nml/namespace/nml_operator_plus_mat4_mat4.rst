:orphan:

nml::mat4 operator+(nml::mat4 lhs, const nml::mat4& rhs)
========================================================

Return a *mat4* that is the sum between two *mat4*.

The sum between two *mat4* is calculated this way:

:math:`\begin{bmatrix} lhs.x.x & lhs.y.x & lhs.z.x & lhs.w.x \\ lhs.x.y & lhs.y.y & lhs.z.y & lhs.w.y \\ lhs.x.z & lhs.y.z & lhs.z.z & lhs.w.z \\ lhs.x.w & lhs.y.w & lhs.z.w & lhs.w.w \end{bmatrix} + \begin{bmatrix} rhs.x.x & rhs.y.x & rhs.z.x & rhs.w.x \\ rhs.x.y & rhs.y.y & rhs.z.y & rhs.w.y \\ rhs.x.z & rhs.y.z & rhs.z.z & rhs.w.z \\ rhs.x.w & rhs.y.w & rhs.z.w & rhs.w.w \end{bmatrix} =`

:math:`\begin{bmatrix} lhs.x.x + rhs.x.x & lhs.y.x + rhs.y.x & lhs.z.x + rhs.z.x & lhs.w.x + rhs.w.x \\ lhs.x.y + rhs.x.y & lhs.y.y + rhs.y.y & lhs.z.y + rhs.z.y & lhs.w.y + rhs.w.y \\ lhs.x.z + rhs.x.z & lhs.y.z + rhs.y.z & lhs.z.z + rhs.z.z & lhs.w.z + rhs.w.z \\ lhs.x.w + rhs.x.w & lhs.y.w + rhs.y.w & lhs.z.w + rhs.z.w & lhs.w.w + rhs.w.w \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat4.h"
	#include <iostream>

	int main() {
		nml::mat4 a(1.0f, 2.0f, 4.0f, 8.0f, 16.0f, 32.0f, 64.0f, 128.0f, 256.0f, 512.0f, 1024.0f, 2048.0f, 4096.0f, 8192.0f, 16384.0f, 32768.0f);
		nml::mat4 b(2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f, 20.0f, 22.0f, 24.0f, 26.0f, 28.0f, 30.0f, 32.0f);
		nml::mat4 c = a + b;
		std::cout << nml::to_string(c) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[3.000000, 6.000000, 10.000000, 16.000000], [26.000000, 44.000000, 78.000000, 144.000000], [274.000000, 532.000000, 1046.000000, 2072.000000], [4122.000000, 8220.000000, 16414.000000, 32800.000000]]