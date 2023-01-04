:orphan:

mat2: nml::mat2& operator-=(const nml::mat2& other)
===================================================

Substract a *mat2* from the current *mat2*.

The difference between two *mat2* is calculated this way:

:math:`\begin{bmatrix} x.x & y.x \\ x.y & y.y \end{bmatrix} - \begin{bmatrix} other.x.x & other.y.x \\ other.x.y & other.y.y \end{bmatrix} = \begin{bmatrix} x.x - other.x.x & y.x - other.y.x \\ x.y - other.x.y & y.y - other.y.y \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat2.h"
	#include <iostream>

	int main() {
		nml::mat2 a(4.0f, 6.0f, 8.0f, 10.0f);
		nml::mat2 b(3.0f, 4.0f, 5.0f, 6.0f);
		a -= b;
		std::cout << nml::to_string(a) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[1.000000, 2.000000], [3.000000, 4.000000]]