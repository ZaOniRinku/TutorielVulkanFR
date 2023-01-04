:orphan:

quat: nml::quat& operator*=(const float other)
==============================================

Multiply the current *quat* by a scalar.

The product between a *quat* and a scalar is calculated this way:

:math:`(a + bi + cj + dk) * other =`

:math:`(a * other) + (b * other)i + (c * other)j + (d * other)k`

Example
-------

.. code-block:: cpp

	#include "include/quat.h"
	#include <iostream>

	int main() {
		nml::quat q(1.0f, 0.25f, 0.5f, 0.75f);
		q *= 2.0f;
		std::cout << nml::to_string(q) << std::endl;

		return 0;
	}

Result:

.. code-block::

	2.000000 + 0.500000i + 1.000000j + 1.500000k