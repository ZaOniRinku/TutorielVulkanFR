:orphan:

quat: float length()
====================

Return the length of the quaternion.

The length of a *quat* is calculated this way:
	
:math:`length = \sqrt{a^2 + b^2 + c^2 + d^2}`

Example
-------

.. code-block:: cpp

	#include "include/quat.h"
	#include <iostream>

	int main() {
		nml::quat a(1.0f, 0.25f, 0.5f, 0.75f);
		std::cout << a.length() << std::endl;
		
		nml::quat b = nml::normalize(a);
		std::cout << b.length() << std::endl;

		return 0;
	}

Result:

.. code-block::

	1.36931
	1