:orphan:

mat2: float* data()
===================

Return a pointer to the matrix's elements.

Example
-------

.. code-block:: cpp

	#include "include/mat2.h"
	#include <iostream>

	int main() {
		nml::mat2 m(1.0f, 2.0f, 3.0f, 4.0f);
		std::cout << *m.data() << std::endl; // Access x.x
		std::cout << *((float*)((char*)m.data() + sizeof(float))) << std::endl; // Access x.y by taking the address of x + the size of a float
		std::cout << *((float*)((char*)m.data() + sizeof(float) * 2)) << std::endl; // Access y.x by taking the address of x + the size of two floats
		std::cout << *((float*)((char*)m.data() + sizeof(float) * 3)) << std::endl; // Access y.y by taking the address of x + the size of three floats

		return 0;
	}

Result:

.. code-block::

	1
	2
	3
	4