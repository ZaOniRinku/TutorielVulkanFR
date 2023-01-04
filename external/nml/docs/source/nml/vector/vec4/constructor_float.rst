:orphan:

vec4: vec4(float _xyzw)
=======================

Construct a (*_xyzw*, *_xyzw*, *_xyzw*, *_xyzw*) vector.

:math:`\begin{bmatrix} \_xyzw \\ \_xyzw \\ \_xyzw \\ \_xyzw \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec4.h"
	#include <iostream>

	int main() {
		nml::vec4 v(1.0f);
		std::cout << nml::to_string(v) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[1.000000, 1.000000, 1.000000, 1.000000]