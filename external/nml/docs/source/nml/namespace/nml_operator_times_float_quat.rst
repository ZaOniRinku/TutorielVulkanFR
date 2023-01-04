:orphan:

nml::quat operator*(float lhs, const nml::quat& rhs)
====================================================

Return a *quat* that is the product between a scalar and a *quat*.

The product between a scalar and a *quat* is calculated this way:

:math:`lhs * (rhs.a + rhs.bi + rhs.cj + rhs.dk) =`

:math:`(lhs * rhs.a) + (lhs * rhs.b)i + (lhs * rhs.c)j + (lhs * rhs.d)k`

Example
-------

.. code-block:: cpp

	#include "include/quat.h"
	#include <iostream>

	int main() {
		nml::quat a(1.0f, 0.25f, 0.5f, 0.75f);
		nml::quat b = 3.0f * a;
		std::cout << nml::to_string(b) << std::endl;

		return 0;
	}

Result:

.. code-block::

	3.000000 + 0.750000i + 1.500000j + 2.250000k