:orphan:

vec2: vec2(float _x, float _y)
==============================

Construct a (*_x*, *_y*) vector.

:math:`\begin{bmatrix} \_x \\ \_y \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec2.h"
	#include <iostream>

	int main() {
		nml::vec2 v(1.0f, 2.0f);
		std::cout << nml::to_string(v) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[1.000000, 2.000000]