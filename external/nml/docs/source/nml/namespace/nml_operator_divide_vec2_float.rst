:orphan:

nml::vec2 operator/(nml::vec2 lhs, const float rhs)
===================================================

Return a *vec2* that is the quotient between a *vec2* and a scalar.

The quotient between a *vec2* and a scalar is calculated this way:

:math:`\frac{\begin{bmatrix} lhs.x \\ lhs.y \end{bmatrix}{rhs} = \begin{bmatrix} \frac{lhs.x}{rhs} \\ \frac{lhs.y}{rhs} \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec2.h"
	#include <iostream>

	int main() {
		nml::vec2 a(1.0f, 2.0f);
		nml::vec2 b = a / 2.0f;
		std::cout << nml::to_string(b) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[0.500000, 1.000000]