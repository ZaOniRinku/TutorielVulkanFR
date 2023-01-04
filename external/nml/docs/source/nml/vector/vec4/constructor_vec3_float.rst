:orphan:

vec4: vec4(nlm::vec3 _xyz, float _w)
====================================

Construct a (*_xyz.x*, *_xyz.y*, *_xyz.z*, *_w*) vector.

:math:`\begin{bmatrix} \_xyz.x \\ \_xyz.y \\ \_xyz.z \\ \_w \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec4.h"
	#include "include/vec3.h"
	#include <iostream>

	int main() {
		nml::vec4 v(nml::vec3(1.0f, 2.0f, 3.0f), 4.0f);
		std::cout << nml::to_string(v) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[1.000000, 2.000000, 3.000000, 4.000000]