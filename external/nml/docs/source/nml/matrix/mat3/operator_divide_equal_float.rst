:orphan:

mat3: nml::mat3& operator/=(const float other)
==============================================

Divide the current *mat3* by a scalar.

The quotient between a *mat3* and a scalar is calculated this way:

:math:`\frac{\begin{bmatrix} x.x & y.x & z.x \\ x.y & y.y & z.y \\ x.z & y.z & z.z \end{bmatrix}}{other} = \begin{bmatrix} \frac{x.x}{other} & \frac{y.x}{other} & \frac{z.x}{other} \\ \frac{x.y}{other} & \frac{y.y}{other} & \frac{z.y}{other} \\ \frac{x.z}{other} & \frac{y.z}{other} & \frac{z.z}{other} \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat3.h"
	#include <iostream>

	int main() {
		nml::mat3 m(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
		m /= 2.0f;
		std::cout << nml::to_string(m) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[0.500000, 1.000000, 1.500000], [2.000000, 2.500000, 3.000000], [3.500000, 4.000000, 4.500000]]