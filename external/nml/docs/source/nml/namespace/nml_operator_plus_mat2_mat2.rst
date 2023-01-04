:orphan:

nml::mat2 operator+(nml::mat2 lhs, const nml::mat2& rhs)
========================================================

Return a *mat2* that is the sum between two *mat2*.

The sum between two *mat2* is calculated this way:

:math:`\begin{bmatrix} lhs.x.x & lhs.y.x \\ lhs.x.y & lhs.y.y \end{bmatrix} + \begin{bmatrix} rhs.x.x & rhs.y.x \\ rhs.x.y & rhs.y.y \end{bmatrix} = \begin{bmatrix} lhs.x.x + rhs.x.x & lhs.y.x + rhs.y.x \\ lhs.x.y + rhs.x.y & lhs.y.y + rhs.y.y \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat2.h"
	#include <iostream>

	int main() {
		nml::mat2 a(1.0f, 2.0f, 4.0f, 8.0f);
		nml::mat2 b(2.0f, 4.0f, 6.0f, 8.0f);
		nml::mat2 c = a + b;
		std::cout << nml::to_string(c) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[3.000000, 6.000000], [10.000000, 16.000000]]