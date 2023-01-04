:orphan:

vec2: float length()
====================

Return the length of the vector.

The length of a *vec2* is calculated this way:
	
:math:`length = \sqrt{x^2 + y^2}`

Example
-------

.. code-block:: cpp

	#include "include/vec2.h"
	#include <iostream>

	int main() {
		nml::vec2 a(1.0f, 2.0f);
		std::cout << a.length() << std::endl;
		
		nml::vec2 b = nml::normalize(a);
		std::cout << b.length() << std::endl;

		return 0;
	}

Result:

.. code-block::

	2.23607
	1