:orphan:

quat: nml::quat& operator/=(const float other)
==============================================

Divide the current *quat* by a scalar.

The quotient between a *quat* and a scalar is calculated this way:

:math:`\frac{(a + bi + cj + dk)}{other} = \frac{a}{other} + \frac{b}{other}i + \frac{c}{other}j + \frac{d}{other}k`

Example
-------

.. code-block:: cpp

	#include "include/quat.h"
	#include <iostream>

	int main() {
		nml::quat q(1.0f, 0.25f, 0.5f, 0.75f);
		q /= 2.0f;
		std::cout << nml::to_string(q) << std::endl;

		return 0;
	}

Result:

.. code-block::

	0.500000 + 0.125000i + 0.250000j + 0.375000k