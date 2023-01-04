:orphan:

bool operator!=(const nml::vec3& lhs, const nml::vec3& rhs)
===========================================================

Return true if the two *vec3* are different, else, return false.

The inequality between two *vec3* is calculated this way:

:math:`\begin{bmatrix} lhs.x \\ lhs.y \\ lhs.z \end{bmatrix} \neq \begin{bmatrix} rhs.x \\ rhs.y \\ rhs.z \end{bmatrix} = (lhs.x \neq rhs.x) or (lhs.y \neq rhs.y) or (lhs.z \neq rhs.z)`

Example
-------

.. code-block:: cpp

	#include "include/vec3.h"
	#include <iostream>

	int main() {
		nml::vec3 a(1.0f, 2.0f, 3.0f);
		nml::vec3 b(3.0f, 2.0f, 4.0f);
		bool c = (a != b);
		std::cout << c << std::endl;

		return 0;
	}

Result:

.. code-block::

	1