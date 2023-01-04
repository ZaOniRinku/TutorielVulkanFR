:orphan:

vec4: nml::vec4& operator/=(const float other)
==============================================

Divide the current *vec4* by a scalar.

The quotient between a *vec4* and a scalar is calculated this way:

:math:`\frac{\begin{bmatrix} x \\ y \\ z \\ w \end{bmatrix}}{other} = \begin{bmatrix} \frac{x}{other} \\ \frac{y}{other} \\ \frac{z}{other} \\ \frac{w}{other} \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec4.h"
	#include <iostream>

	int main() {
		nml::vec4 v(1.0f, 2.0f, 3.0f, 4.0f);
		v /= 2.0f;
		std::cout << nml::to_string(v) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[0.500000, 1.000000, 1.500000, 2.000000]