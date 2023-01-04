:orphan:

nml::vec2 operator+(nml::vec2 lhs, const nml::vec2& rhs)
========================================================

Return a *vec2* that is the sum between two *vec2*.

The sum between two *vec2* is calculated this way:

:math:`\begin{bmatrix} lhs.x \\ lhs.y \end{bmatrix} + \begin{bmatrix} rhs.x \\ rhs.y \end{bmatrix} = \begin{bmatrix} lhs.x + rhs.x \\ lhs.y + rhs.y \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec2.h"
	#include <iostream>

	int main() {
		nml::vec2 a(1.0f, 2.0f);
		nml::vec2 b(2.0f, 4.0f);
		nml::vec2 c = a + b;
		std::cout << nml::to_string(c) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[3.000000, 6.000000]