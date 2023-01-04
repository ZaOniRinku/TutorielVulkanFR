:orphan:

bool operator==(const nml::mat4& lhs, const nml::mat4& rhs)
===========================================================

Return true if the two *mat4* are identical, else, return false.

The equality between two *mat4* is calculated this way:

:math:`\begin{bmatrix} lhs.x.x & lhs.y.x & lhs.z.x & lhs.w.x \\ lhs.x.y & lhs.y.y & lhs.z.y & lhs.w.y \\ lhs.x.z & lhs.y.z & lhs.z.z & lhs.w.z \\ lhs.x.z & lhs.y.z & lhs.z.z & lhs.w.z \end{bmatrix} == \begin{bmatrix} rhs.x.x & rhs.y.x & rhs.z.x & rhs.w.x \\ rhs.x.y & rhs.y.y & rhs.z.y & rhs.w.y \\ rhs.x.z & rhs.y.z & rhs.z.z & rhs.w.z \\ rhs.x.w & rhs.y.w & rhs.z.w & rhs.w.w \end{bmatrix} =`

:math:`\small (lhs.x.x == rhs.x.x) and (lhs.y.x == rhs.y.x) and (lhs.z.x == rhs.z.x) and (lhs.w.x == rhs.w.x) and`
:math:`\small (lhs.x.y == rhs.x.y) and (lhs.y.y == rhs.y.y) and (lhs.z.y == rhs.z.y) and (lhs.w.y == rhs.w.y) and`
:math:`\small (lhs.x.z == rhs.x.z) and (lhs.y.z == rhs.y.z) and (lhs.z.z == rhs.z.z) and (lhs.w.z == rhs.w.z) and`
:math:`\small (lhs.x.w == rhs.x.w) and (lhs.y.w == rhs.y.w) and (lhs.z.w == rhs.z.w) and (lhs.w.w == rhs.w.w)`

Example
-------

.. code-block:: cpp

	#include "include/mat4.h"
	#include <iostream>

	int main() {
		nml::mat4 a(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
		nml::mat4 b = a;
		bool c = (a == b);
		std::cout << c << std::endl;

		return 0;
	}

Result:

.. code-block::

	1