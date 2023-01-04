:orphan:

nml::quat operator/(nml::quat lhs, const float rhs)
===================================================

Return a *quat* that is the quotient between a *quat* and a scalar.

The quotient between a *quat* and a scalar is calculated this way:

:math:`\frac{(lhs.a + lhs.bi + lhs.cj + lhs.dk)}{rhs} = \frac{lhs.a}{rhs} + \frac{lhs.b}{rhs}i + \frac{lhs.c}{rhs}j + \frac{lhs.d}{rhs}k`

Example
-------

.. code-block:: cpp

	#include "include/quat.h"
	#include <iostream>

	int main() {
		nml::quat a(1.0f, 0.25f, 0.5f, 0.75f);
		nml::quat b = a / 2.0f;
		std::cout << nml::to_string(b) << std::endl;

		return 0;
	}

Result:

.. code-block::

	0.500000 + 0.125000i + 0.250000j + 0.375000k