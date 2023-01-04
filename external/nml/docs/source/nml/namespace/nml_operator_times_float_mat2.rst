:orphan:

nml::mat2 operator*(float lhs, const nml::mat2& rhs)
====================================================

Return a *mat2* that is the product between a scalar and a *mat2*.

The product between a scalar and a *mat2* is calculated this way:

:math:`lhs * \begin{bmatrix} rhs.x.x & rhs.y.x \\ rhs.x.y & rhs.y.y \end{bmatrix} = \begin{bmatrix} lhs * rhs.x.x & lhs * rhs.y.x \\ lhs * rhs.x.y & lhs * rhs.y.y \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat2.h"
	#include <iostream>

	int main() {
		nml::mat2 a(1.0f, 2.0f, 3.0f, 4.0f);
		nml::mat2 b = 3.0f * a;
		std::cout << nml::to_string(b) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[3.000000, 6.000000], [9.000000, 12.000000]]