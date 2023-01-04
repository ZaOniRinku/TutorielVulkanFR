:orphan:

bool operator==(const nml::quat& lhs, const nml::quat& rhs)
===========================================================

Return true if the two *quat* are identical, else, return false.

The equality between two *quat* is calculated this way:

:math:`lhs.a + lhs.bi + lhs.cj + lhs.dk == rhs.a + rhs.bi + rhs.cj + rhs.dk =`

:math:`(lhs.a == rhs.a) and (lhs.b == rhs.b) and (lhs.c == rhs.c) and (lhs.d == rhs.d)`

Example
-------

.. code-block:: cpp

	#include "include/quat.h"
	#include <iostream>

	int main() {
		nml::quat a(1.0f, 0.25f, 0.5f, 0.75f);
		nml::quat b = a;
		bool c = (a == b);
		std::cout << c << std::endl;

		return 0;
	}

Result:

.. code-block::

	1