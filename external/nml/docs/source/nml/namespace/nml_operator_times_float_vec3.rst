:orphan:

nml::vec3 operator*(float lhs, const nml::vec3& rhs)
====================================================

Return a *vec3* that is the product between a scalar and a *vec3*.

The product between a scalar and a *vec3* is calculated this way:

:math:`lhs * \begin{bmatrix} rhs.x \\ rhs.y \\ rhs.z \end{bmatrix} = \begin{bmatrix} lhs * rhs.x \\ lhs * rhs.y \\ lhs * rhs.z \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec3.h"
	#include <iostream>

	int main() {
		nml::vec3 a(1.0f, 2.0f, 3.0f);
		nml::vec3 b = 3.0f * a;
		std::cout << nml::to_string(b) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[3.000000, 6.000000, 9.000000]