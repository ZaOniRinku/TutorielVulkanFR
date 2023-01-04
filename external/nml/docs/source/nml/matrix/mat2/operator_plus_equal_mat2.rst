:orphan:

mat2: nml::mat2& operator+=(const nml::mat2& other)
===================================================

Add a *mat2* to the current *mat2*.

The sum between two *mat2* is calculated this way:

:math:`\begin{bmatrix} x.x & y.x \\ x.y & y.y \end{bmatrix} + \begin{bmatrix} other.x.x & other.y.x \\ other.x.y & other.y.y \end{bmatrix} = \begin{bmatrix} x.x + other.x.x & y.x + other.y.x \\ x.y + other.x.y & y.y + other.y.y \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat2.h"
	#include <iostream>

	int main() {
		nml::mat2 a(1.0f, 2.0f, 3.0f, 4.0f);
		nml::mat2 b(3.0f, 4.0f, 5.0f, 6.0f);
		a += b;
		std::cout << nml::to_string(a) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[4.000000, 6.000000], [8.000000, 10.000000]]