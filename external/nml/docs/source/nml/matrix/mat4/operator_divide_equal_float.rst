:orphan:

mat4: nml::mat4& operator/=(const float other)
==============================================

Divide the current *mat4* by a scalar.

The quotient between a *mat4* and a scalar is calculated this way:

:math:`\frac{\begin{bmatrix} x.x & y.x & z.x & w.x \\ x.y & y.y & z.y & w.y \\ x.z & y.z & z.z & w.z \\ x.w & y.w & z.w & w.w \end{bmatrix}}{other} = \begin{bmatrix} \frac{x.x}{other} & \frac{y.x}{other} & \frac{z.x}{other} & \frac{w.x}{other} \\ \frac{x.y}{other} & \frac{y.y}{other} & \frac{z.y}{other} & \frac{w.y}{other} \\ \frac{x.w}{other} & \frac{y.z}{other} & \frac{z.z}{other} & \frac{w.z}{other} \\ \frac{x.w}{other} & \frac{y.w}{other} & \frac{z.w}{other} & \frac{w.w}{other} \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat4.h"
	#include <iostream>

	int main() {
		nml::mat4 m(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
		m /= 2.0f;
		std::cout << nml::to_string(m) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[0.500000, 1.000000, 1.500000, 2.000000], [2.500000, 3.000000, 3.500000, 4.000000], [4.500000, 5.000000, 5.500000, 6.000000], [6.500000, 7.000000, 7.500000, 8.000000]]