:orphan:

nml::vec4 operator+(nml::vec4 lhs, const nml::vec4& rhs)
========================================================

Return a *vec4* that is the sum between two *vec4*.

The sum between two *vec4* is calculated this way:

:math:`\begin{bmatrix} lhs.x \\ lhs.y \\ lhs.z \\ lhs.w \end{bmatrix} + \begin{bmatrix} rhs.x \\ rhs.y \\ rhs.z \\ rhs.w \end{bmatrix} = \begin{bmatrix} lhs.x + rhs.x \\ lhs.y + rhs.y \\ lhs.z + rhs.z \\ lhs.w + rhs.w \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec4.h"
	#include <iostream>

	int main() {
		nml::vec4 a(1.0f, 2.0f, 7.0f, 12.0f);
		nml::vec4 b(2.0f, 4.0f, 5.0f, 7.0f);
		nml::vec4 c = a + b;
		std::cout << nml::to_string(c) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[3.000000, 6.000000, 12.000000, 19.000000]