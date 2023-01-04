:orphan:

nml::quat operator*(nml::quat lhs, const float rhs)
===================================================

Return a *quat* that is the product between a *quat* and a scalar.

The product between a *quat* and a scalar is calculated this way:

:math:`(lhs.a + lhs.bi + lhs.cj + lhs.dk) * rhs =`

:math:`(lhs.a * rhs) + (lhs.b * rhs)i + (lhs.c * rhs)j + (lhs.d * rhs)k`

Example
-------

.. code-block:: cpp

	#include "include/quat.h"
	#include <iostream>

	int main() {
		nml::quat a(1.0f, 0.25f, 0.5f, 0.75f);
		nml::quat b = a * 3.0f;
		std::cout << nml::to_string(b) << std::endl;

		return 0;
	}

Result:

.. code-block::

	3.000000 + 0.750000i + 1.500000j + 2.250000k