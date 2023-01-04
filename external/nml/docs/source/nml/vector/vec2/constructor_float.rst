:orphan:

vec2: vec2(float _xy)
=====================

Construct a (*_xy*, *_xy*) vector.

:math:`\begin{bmatrix} \_xy \\ \_xy \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec2.h"
	#include <iostream>

	int main() {
		nml::vec2 v(1.0f);
		std::cout << nml::to_string(v) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[1.000000, 1.000000]