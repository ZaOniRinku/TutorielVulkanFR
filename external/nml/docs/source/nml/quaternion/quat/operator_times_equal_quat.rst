:orphan:

quat: nml::quat& operator*=(const nml::quat& other)
===================================================

Multiply the current *quat* by a *quat*.

The product between a *quat* and a scalar is calculated this way:

:math:`(a + bi + cj + dk) * (other.a + other.bi + other.cj + other.dk) =`

:math:`((a * other.a) - (b * other.b) - (c * other.c) - (d * other.d)) +`
:math:`((a * other.b) + (b * other.a) + (c * other.d) - (d * other.c))i +`
:math:`((a * other.c) - (b * other.d) + (c * other.a) + (d * other.b))j +`
:math:`((a * other.d) + (b * other.c) - (c * other.b) + (d * other.a))k +`

Example
-------

.. code-block:: cpp

	#include "include/quat.h"
	#include <iostream>

	int main() {
		nml::quat a(1.0f, 0.25f, 0.5f, 0.75f);
		nml::quat b(2.0f, 0.82f, 0.24f, 0.65f);
		a *= b;
		std::cout << nml::to_string(a) << std::endl;

		return 0;
	}

Result:

.. code-block::

	1.187500 + 1.465000i + 1.692500j + 1.800000k