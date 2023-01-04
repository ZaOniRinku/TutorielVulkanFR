:orphan:

nml::quat nml::conjugate(const nml::quat& qua)
==============================================

Return the conjugate of a quaternion.

The conjugate of a *quat* is calculated this way:
	
:math:`conj(qua) = qua.a - qua.bi - qua.cj - qua.dk`

Example
-------

.. code-block:: cpp

	#include "include/quat.h"
	#include <iostream>

	int main() {
		nml::quat a(1.0f, 0.25f, 0.5f, 0.75f);
		std::cout << nml::to_string(a) << std::endl;
		nml::quat b = nml::conjugate(a);
		std::cout << nml::to_string(b) << std::endl;

		return 0;
	}

Result:

.. code-block::

	1.000000 + 0.250000i + 0.500000j + 0.750000k
	1.000000 + -0.250000i + -0.500000j + -0.750000k