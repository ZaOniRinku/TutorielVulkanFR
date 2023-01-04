:orphan:

mat3: float det() const
=======================

Return the determinant of the matrix.

The determinant of a *mat3* is calculated this way:
	
:math:`\small det = x.x * (y.y * z.z - z.y * y.z) - y.x * (x.y * z.z - z.y * x.z) + z.x * (x.y * y.z - y.y * x.z)`

Example
-------

.. code-block:: cpp

	#include "include/mat3.h"
	#include <iostream>

	int main() {
		nml::mat3 m(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 10.0f);
		std::cout << m.det() << std::endl;

		return 0;
	}

Result:

.. code-block::

	-3