:orphan:

nml::mat2 operator*(nml::mat2 lhs, const nml::mat2& rhs)
========================================================

Return a *mat2* that is the product between two *mat2*.

The product between two *mat2* is calculated this way:

:math:`\begin{bmatrix} lhs.x.x & lhs.y.x \\ lhs.x.y & lhs.y.y \end{bmatrix} * \begin{bmatrix} rhs.x.x & rhs.y.x \\ rhs.x.y & rhs.y.y \end{bmatrix} =`

:math:`\begin{bmatrix} lhs.x.x * rhs.x.x + lhs.y.x * rhs.x.y & lhs.x.x * rhs.y.x + lhs.y.x * rhs.y.y \\ lhs.x.y * rhs.x.x + lhs.y.y * rhs.x.y & lhs.x.y * rhs.y.x + lhs.y.y * rhs.y.y \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat2.h"
	#include <iostream>

	int main() {
		nml::mat2 a(1.0f, 2.0f, 3.0f, 4.0f);
		nml::mat2 b = nml::inverse(a);
		nml::mat2 c = a * b;
		std::cout << nml::to_string(c) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[1.000000, 0.000000], [0.000000, 1.000000]]