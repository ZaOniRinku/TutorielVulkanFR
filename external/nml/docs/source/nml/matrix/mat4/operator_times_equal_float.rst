:orphan:

mat4: nml::mat4& operator*=(const float other)
==============================================

Multiply the current *mat4* by a scalar.

The product between a *mat4* and a scalar is calculated this way:

:math:`\begin{bmatrix} x.x & y.x & z.x & w.x \\ x.y & y.y & z.y & w.y \\ x.z & y.z & z.z & w.z \\ x.w & y.w & z.w & w.w \end{bmatrix} * other =`

:math:`\begin{bmatrix} x.x * other & y.x * other & z.x * other & w.x * other \\ x.y * other & y.y * other & z.y * other & w.y * other \\ x.z * other & y.z * other & z.z * other & w.z * other \\ x.w * other & y.w * other & z.w * other & w.w * other \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat4.h"
	#include <iostream>

	int main() {
		nml::mat4 m(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
		m *= 2.0f;
		std::cout << nml::to_string(m) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[2.000000, 4.000000, 6.000000, 8.000000], [10.000000, 12.000000, 14.000000, 16.000000], [18.000000, 20.000000, 22.000000, 24.000000], [26.000000, 28.000000, 30.000000, 32.000000]]