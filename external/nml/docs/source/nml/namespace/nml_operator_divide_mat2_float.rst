:orphan:

nml::mat2 operator/(nml::mat2 lhs, const float rhs)
===================================================

Return a *mat2* that is the quotient between a *mat2* and a scalar.

The quotient between a *mat2* and a scalar is calculated this way:

:math:`\frac{\begin{bmatrix} lhs.x.x & lhs.y.x \\ lhs.x.y & lhs.y.y \end{bmatrix}}{rhs} = \begin{bmatrix} \frac{lhs.x.x}{rhs} & \frac{lhs.y.x}{rhs} \\ \frac{lhs.x.y}{rhs} & \frac{lhs.y.y}{rhs} \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat2.h"
	#include <iostream>

	int main() {
		nml::mat2 a(1.0f, 2.0f, 3.0f, 4.0f);
		nml::mat2 b = a / 2.0f;
		std::cout << nml::to_string(b) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[0.500000, 1.000000], [1.500000, 2.000000]]