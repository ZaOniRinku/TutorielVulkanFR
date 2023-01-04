:orphan:

bool operator!=(const nml::mat4& lhs, const nml::mat4& rhs)
===========================================================

Return true if the two *mat4* are different, else, return false.

The inequality between two *mat4* is calculated this way:

:math:`\begin{bmatrix} lhs.x.x & lhs.y.x & lhs.z.x & lhs.w.x \\ lhs.x.y & lhs.y.y & lhs.z.y & lhs.w.y \\ lhs.x.z & lhs.y.z & lhs.z.z & lhs.w.z \\ lhs.x.z & lhs.y.z & lhs.z.z & lhs.w.z \end{bmatrix} \neq \begin{bmatrix} rhs.x.x & rhs.y.x & rhs.z.x & rhs.w.x \\ rhs.x.y & rhs.y.y & rhs.z.y & rhs.w.y \\ rhs.x.z & rhs.y.z & rhs.z.z & rhs.w.z \\ rhs.x.w & rhs.y.w & rhs.z.w & rhs.w.w \end{bmatrix} =`

:math:`\small (lhs.x.x \neq rhs.x.x) or (lhs.y.x \neq rhs.y.x) or (lhs.z.x \neq rhs.z.x) or (lhs.w.x \neq rhs.w.x) or`
:math:`\small (lhs.x.y \neq rhs.x.y) or (lhs.y.y \neq rhs.y.y) or (lhs.z.y \neq rhs.z.y) or (lhs.w.y \neq rhs.w.y) or`
:math:`\small (lhs.x.z \neq rhs.x.z) or (lhs.y.z \neq rhs.y.z) or (lhs.z.z \neq rhs.z.z) or (lhs.w.z \neq rhs.w.z) or`
:math:`\small (lhs.x.w \neq rhs.x.w) or (lhs.y.w \neq rhs.y.w) or (lhs.z.w \neq rhs.z.w) or (lhs.w.w \neq rhs.w.w)`

Example
-------

.. code-block:: cpp

	#include "include/mat4.h"
	#include <iostream>

	int main() {
		nml::mat4 a(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
		nml::mat4 b(3.0f, 2.0f, 5.0f, 1.0f, 6.0f, 9.0f, 12.0f, 1.0f, 2.0f, 3.0f, 1.0f, 2.0f, 4.0f, 6.0f, 8.0f, 7.0f);
		bool c = (a != b);
		std::cout << c << std::endl;

		return 0;
	}

Result:

.. code-block::

	1