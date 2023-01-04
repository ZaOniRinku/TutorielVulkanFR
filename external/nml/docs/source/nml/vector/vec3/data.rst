:orphan:

vec3: float* data()
===================

Return a pointer to the vector’s elements.

Example
-------

.. code-block:: cpp

	#include "include/vec3.h"
	#include <iostream>

	int main() {
		nml::vec3 v(1.0f, 2.0f, 3.0f);
		std::cout << *v.data() << std::endl; // Access x
		std::cout << *((float*)((char*)v.data() + sizeof(float))) << std::endl; // Access y by taking the address of x + the size of a float
		std::cout << *((float*)((char*)v.data() + sizeof(float) * 2)) << std::endl; // Access z by taking the address of x + the size of two floats

		return 0;
	}

Result:

.. code-block::

	1
	2
	3