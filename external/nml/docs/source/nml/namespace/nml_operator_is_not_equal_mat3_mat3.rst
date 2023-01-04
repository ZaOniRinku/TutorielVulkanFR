:orphan:

bool operator!=(const nml::mat3& lhs, const nml::mat3& rhs)
===========================================================

Return true if the two *mat3* are different, else, return false.

The inequality between two *mat3* is calculated this way:

:math:`\begin{bmatrix} lhs.x.x & lhs.y.x & lhs.z.x \\ lhs.x.y & lhs.y.y & lhs.z.y \\ lhs.x.z & lhs.y.z & lhs.z.z \end{bmatrix} \neq \begin{bmatrix} rhs.x.x & rhs.y.x & rhs.z.x \\ rhs.x.y & rhs.y.y & rhs.z.y \\ rhs.x.z & rhs.y.z & rhs.z.z \end{bmatrix} =`

:math:`\small (lhs.x.x \neq rhs.x.x) or (lhs.y.x \neq rhs.y.x) or (lhs.z.x \neq rhs.z.x) or`
:math:`\small (lhs.x.y \neq rhs.x.y) or (lhs.y.y \neq rhs.y.y) or (lhs.z.y \neq rhs.z.y) or`
:math:`\small (lhs.x.z \neq rhs.x.z) or (lhs.y.z \neq rhs.y.z) or (lhs.z.z \neq rhs.z.z)`

Example
-------

.. code-block:: cpp

	#include "include/mat3.h"
	#include <iostream>

	int main() {
		nml::mat3 a(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
		nml::mat3 b(3.0f, 2.0f, 5.0f, 1.0f, 6.0f, 9.0f, 12.0f, 1.0f, 2.0f);
		bool c = (a != b);
		std::cout << c << std::endl;

		return 0;
	}

Result:

.. code-block::

	1