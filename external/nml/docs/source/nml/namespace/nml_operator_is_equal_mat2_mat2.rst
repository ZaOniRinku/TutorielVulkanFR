:orphan:

bool operator==(const nml::mat2& lhs, const nml::mat2& rhs)
===========================================================

Return true if the two *mat2* are identical, else, return false.

The equality between two *mat2* is calculated this way:

:math:`\small \begin{bmatrix} lhs.x.x & lhs.y.x \\ lhs.x.y & lhs.y.y \end{bmatrix} == \begin{bmatrix} rhs.x.x & rhs.y.x \\ rhs.x.y & rhs.y.y \end{bmatrix} =`

:math:`\small (lhs.x.x == rhs.x.x) and (lhs.y.x == rhs.y.x) and`
:math:`\small (lhs.x.y == rhs.x.y) and (lhs.y.y == rhs.y.y)`

Example
-------

.. code-block:: cpp

	#include "include/mat2.h"
	#include <iostream>

	int main() {
		nml::mat2 a(1.0f, 2.0f, 3.0f, 4.0f);
		nml::mat2 b = a;
		bool c = (a == b);
		std::cout << c << std::endl;

		return 0;
	}

Result:

.. code-block::

	1