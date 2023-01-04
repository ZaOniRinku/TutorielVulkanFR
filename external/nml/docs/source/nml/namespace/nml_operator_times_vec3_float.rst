:orphan:

nml::vec3 operator*(nml::vec3 lhs, const float rhs)
===================================================

Return a *vec3* that is the product between a *vec3* and a scalar.

The product between a *vec3* and a scalar is calculated this way:

:math:`\begin{bmatrix} lhs.x \\ lhs.y \\ lhs.z \end{bmatrix} * rhs = \begin{bmatrix} lhs.x * rhs \\ lhs.y * rhs \\ lhs.z * rhs \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec3.h"
	#include <iostream>

	int main() {
		nml::vec3 a(1.0f, 2.0f, 3.0f);
		nml::vec3 b = a * 3.0f;
		std::cout << nml::to_string(b) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[3.000000, 6.000000, 9.000000]