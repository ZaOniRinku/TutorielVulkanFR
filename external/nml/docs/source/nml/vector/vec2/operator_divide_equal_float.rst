:orphan:

vec2: nml::vec2& operator/=(const float other)
==============================================

Divide the current *vec2* by a scalar.

The quotient between a *vec2* and a scalar is calculated this way:

:math:`\frac{\begin{bmatrix} x \\ y \end{bmatrix}}{other} = \begin{bmatrix} \frac{x}{other} \\ \frac{y}{other} \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec2.h"
	#include <iostream>

	int main() {
		nml::vec2 v(1.0f, 2.0f);
		v /= 2.0f;
		std::cout << nml::to_string(v) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[0.500000, 1.000000]