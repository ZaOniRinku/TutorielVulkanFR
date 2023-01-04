:orphan:

bool operator==(const nml::vec4& lhs, const nml::vec4& rhs)
===========================================================

Return true if the two *vec4* are identical, else, return false.

The equality between two *vec4* is calculated this way:

:math:`\begin{bmatrix} lhs.x \\ lhs.y \\ lhs.z \\ lhs.w \end{bmatrix} == \begin{bmatrix} rhs.x \\ rhs.y \\ rhs.z \\ rhs.w \end{bmatrix} =`

:math:`(lhs.x == rhs.x) and (lhs.y == rhs.y) and (lhs.z == rhs.z) and (lhs.w == rhs.w)`

Example
-------

.. code-block:: cpp

	#include "include/vec4.h"
	#include <iostream>

	int main() {
		nml::vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
		nml::vec4 b = a;
		bool c = (a == b);
		std::cout << c << std::endl;

		return 0;
	}

Result:

.. code-block::

	1