:orphan:

bool operator!=(const nml::quat& lhs, const nml::quat& rhs)
===========================================================

Return true if the two *quat* are different, else, return false.

The inequality between two *quat* is calculated this way:

:math:`lhs.a + lhs.bi + lhs.cj + lhs.dk \neq rhs.a + rhs.bi + rhs.cj + rhs.dk =`

:math:`(lhs.a \neq rhs.a) or (lhs.b \neq rhs.b) or (lhs.c \neq rhs.c) or (lhs.d \neq rhs.d)`

Example
-------

.. code-block:: cpp

	#include "include/quat.h"
	#include <iostream>

	int main() {
		nml::quat a(1.0f, 0.25f, 0.5f, 0.75f);
		nml::quat b(2.0f, 0.25f, 1.0f, 0.5f);
		bool c = (a != b);
		std::cout << c << std::endl;

		return 0;
	}

Result:

.. code-block::

	1