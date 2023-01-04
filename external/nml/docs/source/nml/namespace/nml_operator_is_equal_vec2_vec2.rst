:orphan:

bool operator==(const nml::vec2& lhs, const nml::vec2& rhs)
===========================================================

Return true if the two *vec2* are identical, else, return false.

The equality between two *vec2* is calculated this way:

:math:`\begin{bmatrix} lhs.x \\ lhs.y \end{bmatrix} == \begin{bmatrix} rhs.x \\ rhs.y \end{bmatrix} = (lhs.x == rhs.x) and (lhs.y == rhs.y)`

Example
-------

.. code-block:: cpp

	#include "include/vec2.h"
	#include <iostream>

	int main() {
		nml::vec2 a(1.0f, 2.0f);
		nml::vec2 b = a;
		bool c = (a == b);
		std::cout << c << std::endl;

		return 0;
	}

Result:

.. code-block::

	1