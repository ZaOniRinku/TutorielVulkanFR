:orphan:

mat2: mat2(float _xxxyyxyy)
===========================

Construct a ([*_xxxyyxyy*, *_xxxyyxyy*], [*_xxxyyxyy*, *_xxxyyxyy*]) matrix.

:math:`\begin{bmatrix} \_xxxyyxyy & \_xxxyyxyy \\ \_xxxyyxyy & \_xxxyyxyy \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat2.h"
	#include <iostream>

	int main() {
		nml::mat2 m(1.0f);
		std::cout << nml::to_string(m) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[1.000000, 1.000000], [1.000000, 1.000000]]