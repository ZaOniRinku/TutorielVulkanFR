:orphan:

vec4: vec4(nlm::vec2 _xy, nlm::vec2 _zw)
========================================

Construct a (*_xy.x*, *_xy.y*, *_zw.x*, *_zw.y*) vector.

:math:`\begin{bmatrix} \_xy.x \\ \_xy.y \\ \_zw.x \\ \_zw.y \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec4.h"
	#include "include/vec2.h"
	#include <iostream>

	int main() {
		nml::vec4 v(nml::vec2(1.0f, 2.0f), nml::vec2(3.0f, 4.0f));
		std::cout << nml::to_string(v) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[1.000000, 2.000000, 3.000000, 4.000000]