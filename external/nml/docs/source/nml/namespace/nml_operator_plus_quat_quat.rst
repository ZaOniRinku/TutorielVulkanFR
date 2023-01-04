:orphan:

nml::quat operator+(nml::quat lhs, const nml::quat& rhs)
========================================================

Return a *quat* that is the sum between two *quat*.

The sum between two *quat* is calculated this way:

:math:`(lhs.a + lhs.bi + lhs.cj + lhs.dk) + (rhs.a + rhs.bi + rhs.cj + rhs.dk) =`

:math:`(lhs.a + rhs.a) + (lhs.b + rhs.b)i + (lhs.c + rhs.c)j + (lhs.d + rhs.d)k`

Example
-------

.. code-block:: cpp

	#include "include/quat.h"
	#include <iostream>

	int main() {
		nml::quat a(1.0f, 0.25f, 0.5f, 0.75f);
		nml::quat b(2.0f, 0.25f, 1.0f, 0.5f);
		nml::quat c = a + b;
		std::cout << nml::to_string(c) << std::endl;

		return 0;
	}

Result:

.. code-block::

	3.000000 + 0.500000i + 1.500000j + 1.250000k