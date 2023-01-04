:orphan:

bool operator==(const nml::mat3& lhs, const nml::mat3& rhs)
===========================================================

Return true if the two *mat3* are identical, else, return false.

The equality between two *mat3* is calculated this way:

:math:`\begin{bmatrix} lhs.x.x & lhs.y.x & lhs.z.x \\ lhs.x.y & lhs.y.y & lhs.z.y \\ lhs.x.z & lhs.y.z & lhs.z.z \end{bmatrix} == \begin{bmatrix} rhs.x.x & rhs.y.x & rhs.z.x \\ rhs.x.y & rhs.y.y & rhs.z.y \\ rhs.x.z & rhs.y.z & rhs.z.z \end{bmatrix} =`

:math:`\small (lhs.x.x == rhs.x.x) and (lhs.y.x == rhs.y.x) and (lhs.z.x == rhs.z.x) and`
:math:`\small (lhs.x.y == rhs.x.y) and (lhs.y.y == rhs.y.y) and (lhs.z.y == rhs.z.y) and`
:math:`\small (lhs.x.z == rhs.x.z) and (lhs.y.z == rhs.y.z) and (lhs.z.z == rhs.z.z)`

Example
-------

.. code-block:: cpp

	#include "include/mat3.h"
	#include <iostream>

	int main() {
		nml::mat3 a(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
		nml::mat3 b = a;
		bool c = (a == b);
		std::cout << c << std::endl;

		return 0;
	}

Result:

.. code-block::

	1