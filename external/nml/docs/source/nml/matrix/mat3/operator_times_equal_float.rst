:orphan:

mat3: nml::mat3& operator*=(const float other)
==============================================

Multiply the current *mat3* by a scalar.

The product between a *mat3* and a scalar is calculated this way:

:math:`\begin{bmatrix} x.x & y.x & z.x \\ x.y & y.y & z.y \\ x.z & y.z & z.z \end{bmatrix} * other = \begin{bmatrix} x.x * other & y.x * other & z.x * other \\ x.y * other & y.y * other & z.y * other \\ x.z * other & y.z * other & z.z * other \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat3.h"
	#include <iostream>

	int main() {
		nml::mat3 m(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
		m *= 2.0f;
		std::cout << nml::to_string(m) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[2.000000, 4.000000, 6.000000], [8.000000, 10.000000, 12.000000], [14.000000, 16.000000, 18.000000]]