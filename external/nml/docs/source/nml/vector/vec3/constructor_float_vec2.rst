:orphan:

vec3: vec3(float _x, nml::vec2 _yz)
===================================

Construct a (*_x*, *_yz.x*, *_yz.y*) vector.

:math:`\begin{bmatrix} \_x \\ \_yz.x \\ \_yz.y \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec3.h"
	#include "include/vec2.h"
	#include <iostream>

	int main() {
		nml::vec3 v(1.0f, nml::vec2(2.0f, 3.0f));
		std::cout << nml::to_string(v) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[1.000000, 2.000000, 3.000000]