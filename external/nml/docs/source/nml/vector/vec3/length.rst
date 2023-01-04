:orphan:

vec3: float length()
====================

Return the length of the vector.

The length of a *vec3* is calculated this way:
	
:math:`length = \sqrt{x^2 + y^2 + z^2}`

Example
-------

.. code-block:: cpp

	#include "include/vec3.h"
	#include <iostream>

	int main() {
		nml::vec3 a(1.0f, 2.0f, 3.0f);
		std::cout << a.length() << std::endl;
		
		nml::vec3 b = nml::normalize(a);
		std::cout << b.length() << std::endl;

		return 0;
	}

Result:

.. code-block::

	3.74166
	1