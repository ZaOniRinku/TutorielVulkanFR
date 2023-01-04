:orphan:

nml::mat2 inverse(const nml::mat2& mat)
=======================================

Return the inverse of a *mat2*.

The inverse of a *mat2* is calculated this way:

:math:`mat^{-1} = \frac{1.0}{det(mat)} * \begin{bmatrix} y.y & -y.x \\ -x.y & x.x \end{bmatrix}`

**The inverse function does not check if the matrix is invertible (determinant not null).**

Example
-------

.. code-block:: cpp

	#include "include/mat2.h"
	#include <iostream>

	int main() {
		nml::mat2 a(1.0f, 2.0f, 3.0f, 4.0f); // Determinant of a = -2, the matrix is invertible
		nml::mat2 b(1.0f, 2.0f, 1.0f, 2.0f); // Determinant of b = 0, the matrix is not invertible
		nml::mat2 invA = nml::inverse(a);
		nml::mat2 invB = nml::inverse(b); // Undefined behaviour
		std::cout << nml::to_string(invA) << std::endl;
		std::cout << nml::to_string(invB) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[-2.000000, 1.000000], [1.500000, -0.500000]]
	[[inf, -inf], [-inf, inf]]