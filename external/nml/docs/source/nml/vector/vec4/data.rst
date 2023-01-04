:orphan:

vec4: float* data()
===================

Return a pointer to the vector’s elements.

Example
-------

.. code-block:: cpp

	#include "include/vec4.h"
	#include <iostream>

	int main() {
		nml::vec4 v(1.0f, 2.0f, 3.0f, 4.0f);
		std::cout << *v.data() << std::endl; // Access x
		std::cout << *((float*)((char*)v.data() + sizeof(float))) << std::endl; // Access y by taking the address of x + the size of a float
		std::cout << *((float*)((char*)v.data() + sizeof(float) * 2)) << std::endl; // Access z by taking the address of x + the size of two floats
		std::cout << *((float*)((char*)v.data() + sizeof(float) * 3)) << std::endl; // Access w by taking the address of x + the size of three floats

		return 0;
	}

Result:

.. code-block::

	1
	2
	3
	4