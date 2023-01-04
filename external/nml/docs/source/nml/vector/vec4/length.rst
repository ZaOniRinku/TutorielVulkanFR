:orphan:

vec4: float length()
====================

Return the length of the vector.

The length of a *vec4* is calculated this way:
	
:math:`length = \sqrt{x^2 + y^2 + z^2 + w^2}`

Example
-------

.. code-block:: cpp

	#include "include/vec4.h"
	#include <iostream>

	int main() {
		nml::vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
		std::cout << a.length() << std::endl;
		
		nml::vec4 b = nml::normalize(a);
		std::cout << b.length() << std::endl;

		return 0;
	}

Result:

.. code-block::

	5.47723
	1