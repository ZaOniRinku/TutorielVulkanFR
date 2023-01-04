:orphan:

nml::vec4 operator*(nml::mat4 lhs, const nml::vec4& rhs)
========================================================

Return a *vec4* that is the product between a *mat4* and a *vec4*.

The product between a *mat4* and a *vec4* is calculated this way:

:math:`\begin{bmatrix} lhs.x.x & lhs.y.x & lhs.z.x & lhs.w.x \\ lhs.x.y & lhs.y.y & lhs.z.y & lhs.w.y \\ lhs.x.z & lhs.y.z & lhs.z.z & lhs.w.z \\ lhs.x.w & lhs.y.w & lhs.z.w & lhs.w.w \end{bmatrix} * \begin{bmatrix} rhs.x \\ rhs.y \\ rhs.z \\ rhs.w \end{bmatrix} =`

:math:`\begin{bmatrix} lhs.x.x * rhs.x + lhs.y.x * rhs.y + lhs.z.x * rhs.z + lhs.w.x * rhs.w \\ lhs.x.y * rhs.x + lhs.y.y * rhs.y + lhs.z.y * rhs.z + lhs.w.y * rhs.w \\ lhs.x.z * rhs.x + lhs.y.z * rhs.y + lhs.z.z * rhs.z + lhs.w.z * rhs.w \\ lhs.x.w * rhs.x + lhs.y.w * rhs.y + lhs.z.w * rhs.z + lhs.w.w * rhs.w \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat4.h"
	#include <iostream>

	int main() {
		nml::mat4 a(2.0f, 4.0f, 2.5f, 0.25f, 3.0f, 1.5f, 0.25f, 1.25f, 1.0f, 5.25f, 2.25f, 4.5f, 2.0f, 2.25f, 3.5f, 4.5f);
		nml::vec4 b(0.5f, 1.25f, 2.5f, 5.25f);
		nml::vec4 c = a * b;
		std::cout << nml::to_string(c) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[17.750000, 28.812500, 25.562500, 36.562500]