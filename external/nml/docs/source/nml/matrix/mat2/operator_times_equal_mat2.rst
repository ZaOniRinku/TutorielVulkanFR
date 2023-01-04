:orphan:

mat2: nml::mat2& operator*=(const nlm::mat2& other)
===================================================

Multiply the current *mat2* by a *mat2*.

The product between two *mat2* is calculated this way:

:math:`\begin{bmatrix} x.x & y.x \\ x.y & y.y \end{bmatrix} * \begin{bmatrix} other.x.x & other.y.x \\ other.x.y & other.y.y \end{bmatrix} =`

:math:`\begin{bmatrix} x.x * other.x.x + y.x * other.x.y & x.x * other.y.x + y.x * other.y.y \\ x.y * other.x.x + y.y * other.x.y & x.y * other.y.x + y.y * other.y.y \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat2.h"
	#include <iostream>

	int main() {
		nml::mat2 a(1.0f, 2.0f, 3.0f, 4.0f);
		nml::mat2 b = nml::inverse(a);
		a *= b;
		std::cout << nml::to_string(a) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[1.000000, 0.000000], [0.000000, 1.000000]]