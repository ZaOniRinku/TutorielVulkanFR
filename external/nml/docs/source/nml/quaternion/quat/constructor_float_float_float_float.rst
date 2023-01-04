:orphan:

quat: quat(float _a, float _b, float _c, float _d)
==================================================

Construct a (*_a*, *_b*, *_c*, *_d*) quaternion.

:math:`\_a + \_bi + \_cj + \_dk`

Example
-------

.. code-block:: cpp

	#include "include/quat.h"
	#include <iostream>

	int main() {
		nml::quat q(1.0f, 0.25f, 0.5f, 0.75f);
		std::cout << nml::to_string(q) << std::endl;

		return 0;
	}

Result:

.. code-block::

	1.000000 + 0.250000i + 0.500000j + 0.750000k