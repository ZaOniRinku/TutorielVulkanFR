:orphan:

nml::vec2 operator*(nml::mat2 lhs, const nml::vec2& rhs)
========================================================

Return a *vec2* that is the product between a *mat2* and a *vec2*.

The product between a *mat2* and a *vec2* is calculated this way:

:math:`\begin{bmatrix} lhs.x.x & lhs.y.x \\ lhs.x.y & lhs.y.y \end{bmatrix} * \begin{bmatrix} rhs.x \\ rhs.y \end{bmatrix} =`

:math:`\begin{bmatrix} lhs.x.x * rhs.x + lhs.y.x * rhs.y \\ lhs.x.y * rhs.x + lhs.y.y * rhs.y \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat2.h"
	#include <iostream>

	int main() {
		nml::mat2 a(2.0f, 4.0f, 3.0f, 1.5f);
		nml::vec2 b(0.5f, 1.25f);
		nml::vec2 c = a * b;
		std::cout << nml::to_string(c) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[4.750000, 3.875000]