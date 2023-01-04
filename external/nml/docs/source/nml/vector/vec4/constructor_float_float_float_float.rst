:orphan:

vec4: vec4(float _x, float _y, float _z, float _w)
==================================================

Construct a (*_x*, *_y*, *_z*, *_w*) vector.

:math:`\begin{bmatrix} \_x \\ \_y \\ \_z \\ \_w \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec4.h"
	#include <iostream>

	int main() {
		nml::vec4 v(1.0f, 2.0f, 3.0f, 4.0f);
		std::cout << nml::to_string(v) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[1.000000, 2.000000, 3.000000, 4.000000]