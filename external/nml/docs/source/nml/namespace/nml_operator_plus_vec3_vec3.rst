:orphan:

nml::vec3 operator+(nml::vec3 lhs, const nml::vec3& rhs)
========================================================

Return a *vec3* that is the sum between two *vec3*.

The sum between two *vec3* is calculated this way:

:math:`\begin{bmatrix} lhs.x \\ lhs.y \\ lhs.z \end{bmatrix} + \begin{bmatrix} rhs.x \\ rhs.y \\ rhs.z \end{bmatrix} = \begin{bmatrix} lhs.x + rhs.x \\ lhs.y + rhs.y \\ lhs.z + rhs.z \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec3.h"
	#include <iostream>

	int main() {
		nml::vec3 a(1.0f, 2.0f, 7.0f);
		nml::vec3 b(2.0f, 4.0f, 5.0f);
		nml::vec3 c = a + b;
		std::cout << nml::to_string(c) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[3.000000, 6.000000, 12.000000]