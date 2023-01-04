:orphan:

nml::vec4 operator*(nml::vec4 lhs, const float rhs)
===================================================

Return a *vec4* that is the product between a *vec4* and a scalar.

The product between a *vec4* and a scalar is calculated this way:

:math:`\begin{bmatrix} lhs.x \\ lhs.y \\ lhs.z \\ lhs.w \end{bmatrix} * rhs = \begin{bmatrix} lhs.x * rhs \\ lhs.y * rhs \\ lhs.z * rhs \\ lhs.w * rhs \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec4.h"
	#include <iostream>

	int main() {
		nml::vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
		nml::vec4 b = a * 3.0f;
		std::cout << nml::to_string(b) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[3.000000, 6.000000, 9.000000, 12.000000]