:orphan:

vec3: vec3(float _x, float _y, float _z)
========================================

Construct a (*_x*, *_y*, *_z*) vector.

:math:`\begin{bmatrix} \_x \\ \_y \\ \_z \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec3.h"
	#include <iostream>

	int main() {
		nml::vec3 v(1.0f, 2.0f, 3.0f);
		std::cout << nml::to_string(v) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[1.000000, 2.000000, 3.000000]