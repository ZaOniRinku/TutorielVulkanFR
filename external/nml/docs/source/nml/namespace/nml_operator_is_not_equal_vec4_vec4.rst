:orphan:

bool operator!=(const nml::vec4& lhs, const nml::vec4& rhs)
===========================================================

Return true if the two *vec4* are different, else, return false.

The inequality between two *vec4* is calculated this way:

:math:`\begin{bmatrix} lhs.x \\ lhs.y \\ lhs.z \\ lhs.w \end{bmatrix} \neq \begin{bmatrix} rhs.x \\ rhs.y \\ rhs.z \\ rhs.w \end{bmatrix} =`

:math:`(lhs.x \neq rhs.x) or (lhs.y \neq rhs.y) or (lhs.z \neq rhs.z) or (lhs.w \neq rhs.w)`

Example
-------

.. code-block:: cpp

	#include "include/vec4.h"
	#include <iostream>

	int main() {
		nml::vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
		nml::vec4 b(3.0f, 2.0f, 4.0f, 5.0f);
		bool c = (a != b);
		std::cout << c << std::endl;

		return 0;
	}

Result:

.. code-block::

	1