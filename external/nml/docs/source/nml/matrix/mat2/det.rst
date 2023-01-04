:orphan:

mat2: float det() const
=======================

Return the determinant of the matrix.

The determinant of a *mat2* is calculated this way:
	
:math:`det = x.x * y.y - y.x * x.y`

Example
-------

.. code-block:: cpp

	#include "include/mat2.h"
	#include <iostream>

	int main() {
		nml::mat2 m(1.0f, 2.0f, 3.0f, 4.0f);
		std::cout << m.det() << std::endl;

		return 0;
	}

Result:

.. code-block::

	-2