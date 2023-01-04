:orphan:

quat: nml::quat& operator-=(const nml::quat& other)
===================================================

Substract a *quat* from the current *quat*.

The difference between two *quat* is calculated this way:

:math:`(a + bi + cj + dk) - (other.a + other.bi + other.cj + other.dk) =`

:math:`(a - other.a) + (b - other.b)i + (c - other.c)j + (d - other.d)k`

Example
-------

.. code-block:: cpp

	#include "include/quat.h"
	#include <iostream>

	int main() {
		nml::quat a(1.0f, 0.25f, 0.5f, 0.75f);
		nml::quat b(2.0f, 0.82f, 0.24f, 0.65f);
		a -= b;
		std::cout << nml::to_string(a) << std::endl;

		return 0;
	}

Result:

.. code-block::

	-1.000000 + -0.570000i + 0.260000j + 0.100000k