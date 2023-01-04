:orphan:

bool operator!=(const nml::mat2& lhs, const nml::mat2& rhs)
===========================================================

Return true if the two *mat2* are different, else, return false.

The inequality between two *mat2* is calculated this way:

:math:`\small \begin{bmatrix} lhs.x.x & lhs.y.x \\ lhs.x.y & lhs.y.y \end{bmatrix} \neq \begin{bmatrix} rhs.x.x & rhs.y.x \\ rhs.x.y & rhs.y.y \end{bmatrix} =`

:math:`\small (lhs.x.x \neq rhs.x.x) or (lhs.y.x \neq rhs.y.x) or`
:math:`\small (lhs.x.y \neq rhs.x.y) or (lhs.y.y \neq rhs.y.y)`

Example
-------

.. code-block:: cpp

	#include "include/mat2.h"
	#include <iostream>

	int main() {
		nml::mat2 a(1.0f, 2.0f, 3.0f, 4.0f);
		nml::mat2 b(3.0f, 2.0f, 5.0f, 1.0f);
		bool c = (a != b);
		std::cout << c << std::endl;

		return 0;
	}

Result:

.. code-block::

	1