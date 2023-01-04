:orphan:

nml::vec3 operator*(nml::mat3 lhs, const nml::vec3& rhs)
========================================================

Return a *vec3* that is the product between a *mat3* and a *vec3*.

The product between a *mat3* and a *vec3* is calculated this way:

:math:`\begin{bmatrix} lhs.x.x & lhs.y.x & lhs.z.x \\ lhs.x.y & lhs.y.y & lhs.z.y \\ lhs.x.z & lhs.y.z & lhs.z.z \end{bmatrix} * \begin{bmatrix} rhs.x \\ rhs.y \\ rhs.z \end{bmatrix} =`

:math:`\begin{bmatrix} lhs.x.x * rhs.x + lhs.y.x * rhs.y + lhs.z.x * rhs.z \\ lhs.x.y * rhs.x + lhs.y.y * rhs.y + lhs.z.y * rhs.z \\ lhs.x.z * rhs.x + lhs.y.z * rhs.y + lhs.z.z * rhs.z \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat3.h"
	#include <iostream>

	int main() {
		nml::mat3 a(2.0f, 4.0f, 2.5f, 3.0f, 1.5f, 0.25f, 1.0f, 5.25f, 2.25f);
		nml::vec3 b(0.5f, 1.25f, 2.5f);
		nml::vec3 c = a * b;
		std::cout << nml::to_string(c) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[7.250000, 17.000000, 7.187500]