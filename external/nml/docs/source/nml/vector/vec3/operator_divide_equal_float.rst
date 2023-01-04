:orphan:

vec3: nml::vec3& operator/=(const float other)
==============================================

Divide the current *vec3* by a scalar.

The quotient between a *vec3* and a scalar is calculated this way:

:math:`\frac{\begin{bmatrix} x \\ y \\ z \end{bmatrix}}{other} = \begin{bmatrix} \frac{x}{other} \\ \frac{y}{other} \\ \frac{z}{other} \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec3.h"
	#include <iostream>

	int main() {
		nml::vec3 v(1.0f, 2.0f, 3.0f);
		v /= 2.0f;
		std::cout << nml::to_string(v) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[0.500000, 1.000000, 1.500000]