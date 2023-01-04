:orphan:

nml::vec2 operator*(float lhs, const nml::vec2& rhs)
====================================================

Return a *vec2* that is the product between a scalar and a *vec2*.

The product between a scalar and a *vec2* is calculated this way:

:math:`lhs * \begin{bmatrix} rhs.x \\ rhs.y \end{bmatrix} = \begin{bmatrix} lhs * rhs.x \\ lhs * rhs.y \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec2.h"
	#include <iostream>

	int main() {
		nml::vec2 a(1.0f, 2.0f);
		nml::vec2 b = 3.0f * a;
		std::cout << nml::to_string(b) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[3.000000, 6.000000]