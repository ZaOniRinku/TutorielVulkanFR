:orphan:

nml::vec4 operator*(float lhs, const nml::vec4& rhs)
====================================================

Return a *vec4* that is the product between a scalar and a *vec4*.

The product between a scalar and a *vec4* is calculated this way:

:math:`lhs * \begin{bmatrix} rhs.x \\ rhs.y \\ rhs.z \\ rhs.w \end{bmatrix} = \begin{bmatrix} lhs * rhs.x \\ lhs * rhs.y \\ lhs * rhs.z \\ lhs * rhs.w \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec4.h"
	#include <iostream>

	int main() {
		nml::vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
		nml::vec4 b = 3.0f * a;
		std::cout << nml::to_string(b) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[3.000000, 6.000000, 9.000000, 12.000000]