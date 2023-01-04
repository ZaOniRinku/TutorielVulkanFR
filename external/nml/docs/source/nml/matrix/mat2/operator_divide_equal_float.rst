:orphan:

mat2: nml::mat2& operator/=(const float other)
==============================================

Divide the current *mat2* by a scalar.

The quotient between a *mat2* and a scalar is calculated this way:

:math:`\frac{\begin{bmatrix} x.x & y.x \\ x.y & y.y \end{bmatrix}}{other} = \begin{bmatrix} \frac{x.x}{other} & \frac{y.x}{other} \\ \frac{x.y}{other} & \frac{y.y}{other} \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat2.h"
	#include <iostream>

	int main() {
		nml::mat2 m(1.0f, 2.0f, 3.0f, 4.0f);
		m /= 2.0f;
		std::cout << nml::to_string(m) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[0.500000, 1.000000], [1.500000, 2.000000]]