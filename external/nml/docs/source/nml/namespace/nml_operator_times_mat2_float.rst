:orphan:

nml::mat2 operator*(nml::mat2 lhs, const float rhs)
===================================================

Return a *mat2* that is the product between a *mat2* and a scalar.

The product between a *mat2* and a scalar is calculated this way:

:math:`\begin{bmatrix} lhs.x.x & lhs.y.x \\ lhs.x.y & lhs.y.y \end{bmatrix} * rhs = \begin{bmatrix} lhs.x.x * rhs & lhs.y.x * rhs \\ lhs.x.y * rhs & lhs.y.y * rhs \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat2.h"
	#include <iostream>

	int main() {
		nml::mat2 a(1.0f, 2.0f, 3.0f, 4.0f);
		nml::mat2 b = a * 3.0f;
		std::cout << nml::to_string(b) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[3.000000, 6.000000], [9.000000, 12.000000]]