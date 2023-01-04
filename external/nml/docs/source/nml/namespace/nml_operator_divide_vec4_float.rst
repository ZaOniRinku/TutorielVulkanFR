:orphan:

nml::vec4 operator/(nml::vec4 lhs, const float rhs)
===================================================

Return a *vec4* that is the quotient between a *vec4* and a scalar.

The quotient between a *vec4* and a scalar is calculated this way:

:math:`\frac{\begin{bmatrix} lhs.x \\ lhs.y \\ lhs.z \\ lhs.w \end{bmatrix}}{rhs} = \begin{bmatrix} \frac{lhs.x}{rhs} \\ \frac{lhs.y}{rhs} \\ \frac{lhs.z}{rhs} \\ \frac{lhs.w}{rhs} \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec4.h"
	#include <iostream>

	int main() {
		nml::vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
		nml::vec4 b = a / 2.0f;
		std::cout << nml::to_string(b) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[0.500000, 1.000000, 1.500000, 2.000000]