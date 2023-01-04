:orphan:

mat2: mat2()
============

Construct a ([1.0, 0.0], [0.0, 1.0]) identity matrix.

:math:`\begin{bmatrix} 1.0 & 0.0 \\ 0.0 & 1.0 \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat2.h"
	#include <iostream>

	int main() {
		nml::mat2 m;
		std::cout << nml::to_string(m) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[1.000000, 0.000000], [0.000000, 1.000000]]