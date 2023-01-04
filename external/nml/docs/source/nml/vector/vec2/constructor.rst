:orphan:

vec2: vec2()
============

Construct a (0.0, 0.0) vector.

:math:`\begin{bmatrix} 0.0 \\ 0.0 \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec2.h"
	#include <iostream>

	int main() {
		nml::vec2 v;
		std::cout << nml::to_string(v) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[0.000000, 0.000000]