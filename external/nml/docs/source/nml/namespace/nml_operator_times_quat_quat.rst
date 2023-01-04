:orphan:

nml::quat operator*(nml::quat lhs, const nml::quat& rhs)
=========================================================

Return a *quat* that is the product between a *quat* and a scalar.

The product between a *quat* and a scalar is calculated this way:

:math:`(lhs.a + lhs.bi + lhs.cj + lhs.dk) * (rhs.a + rhs.bi + rhs.cj + rhs.dk) =`

:math:`((lhs.a * rhs.a) - (lhs.b * rhs.b) - (lhs.c * rhs.c) - (lhs.d * rhs.d)) +`
:math:`((lhs.a * rhs.b) + (lhs.b * rhs.a) + (lhs.c * rhs.d) - (lhs.d * rhs.c))i +`
:math:`((lhs.a * rhs.c) - (lhs.b * rhs.d) + (lhs.c * rhs.a) + (lhs.d * rhs.b))j +`
:math:`((lhs.a * rhs.d) + (lhs.b * rhs.c) - (lhs.c * rhs.b) + (lhs.d * rhs.a))k +`

Example
-------

.. code-block:: cpp

	#include "include/quat.h"
	#include <iostream>

	int main() {
		nml::quat a(1.0f, 0.25f, 0.5f, 0.75f);
		nml::quat b(2.0f, 0.82f, 0.24f, 0.65f);
		nml::quat c = a * b;
		std::cout << nml::to_string(c) << std::endl;

		return 0;
	}

Result:

.. code-block::

	1.187500 + 1.465000i + 1.692500j + 1.800000k