:orphan:

bool operator==(const nml::vec3& lhs, const nml::vec3& rhs)
===========================================================

Return true if the two *vec3* are identical, else, return false.

The equality between two *vec3* is calculated this way:

:math:`\begin{bmatrix} lhs.x \\ lhs.y \\ lhs.z \end{bmatrix} == \begin{bmatrix} rhs.x \\ rhs.y \\ rhs.z \end{bmatrix} = (lhs.x == rhs.x) and (lhs.y == rhs.y) and (lhs.z == rhs.z)`

Example
-------

.. code-block:: cpp

	#include "include/vec3.h"
	#include <iostream>

	int main() {
		nml::vec3 a(1.0f, 2.0f, 3.0f);
		nml::vec3 b = a;
		bool c = (a == b);
		std::cout << c << std::endl;

		return 0;
	}

Result:

.. code-block::

	1