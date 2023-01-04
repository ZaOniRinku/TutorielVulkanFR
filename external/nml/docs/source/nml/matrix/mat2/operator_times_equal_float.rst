:orphan:

mat2: nml::mat2& operator*=(const float other)
==============================================

Multiply the current *mat2* by a scalar.

The product between a *mat2* and a scalar is calculated this way:

:math:`\begin{bmatrix} x.x & y.x \\ x.y & y.y \end{bmatrix} * other = \begin{bmatrix} x.x * other & y.x * other \\ x.y * other & y.y * other \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat2.h"
	#include <iostream>

	int main() {
		nml::mat2 m(1.0f, 2.0f, 3.0f, 4.0f);
		m *= 2.0f;
		std::cout << nml::to_string(m) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[2.000000, 4.000000], [6.000000, 8.000000]]