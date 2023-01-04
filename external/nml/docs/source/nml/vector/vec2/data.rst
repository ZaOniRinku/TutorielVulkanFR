:orphan:

vec2: float* data()
===================

Return a pointer to the vector’s elements.

Example
-------

.. code-block:: cpp

	#include "include/vec2.h"
	#include <iostream>

	int main() {
		nml::vec2 v(1.0f, 2.0f);
		std::cout << *v.data() << std::endl; // Access x
		std::cout << *((float*)((char*)v.data() + sizeof(float))) << std::endl; // Access y by taking the address of x + the size of a float

		return 0;
	}

Result:

.. code-block::

	1
	2