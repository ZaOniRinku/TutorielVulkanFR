:orphan:

vec3: vec3(nml::vec2 _xy, float _z)
===================================

Construct a (*_xy.x*, *_xy.y*, *_z*) vector.

:math:`\begin{bmatrix} \_xy.x \\ \_xy.y \\ \_z \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec3.h"
	#include "include/vec2.h"
	#include <iostream>

	int main() {
		nml::vec3 v(nml::vec2(1.0f, 2.0f), 3.0f);
		std::cout << nml::to_string(v) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[1.000000, 2.000000, 3.000000]