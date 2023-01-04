:orphan:

vec4: vec4(float _x, nlm::vec3 _yzw)
====================================

Construct a (*_x*, *_yzw.x*, *_yzw.y*, *_yzw.z*) vector.

:math:`\begin{bmatrix} \_x \\ \_yzw.x \\ \_yzw.y \\ \_yzw.z \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec4.h"
	#include "include/vec3.h"
	#include <iostream>

	int main() {
		nml::vec4 v(1.0f, nml::vec3(2.0f, 3.0f, 4.0f));
		std::cout << nml::to_string(v) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[1.000000, 2.000000, 3.000000, 4.000000]