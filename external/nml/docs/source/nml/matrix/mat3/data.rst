:orphan:

mat3: float* data()
===================

Return a pointer to the matrix's elements.

Example
-------

.. code-block:: cpp

	#include "include/mat3.h"
	#include <iostream>

	int main() {
		nml::mat3 m(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
		std::cout << *m.data() << std::endl; // Access x.x
		std::cout << *((float*)((char*)m.data() + sizeof(float))) << std::endl; // Access x.y by taking the address of x + the size of a float
		std::cout << *((float*)((char*)m.data() + sizeof(float) * 2)) << std::endl; // Access x.z by taking the address of x + the size of two floats
		std::cout << *((float*)((char*)m.data() + sizeof(float) * 3)) << std::endl; // Access y.x by taking the address of x + the size of three floats
		std::cout << *((float*)((char*)m.data() + sizeof(float) * 4)) << std::endl; // Access y.y by taking the address of x + the size of four floats
		std::cout << *((float*)((char*)m.data() + sizeof(float) * 5)) << std::endl; // Access y.z by taking the address of x + the size of five floats
		std::cout << *((float*)((char*)m.data() + sizeof(float) * 6)) << std::endl; // Access z.x by taking the address of x + the size of six floats
		std::cout << *((float*)((char*)m.data() + sizeof(float) * 7)) << std::endl; // Access z.y by taking the address of x + the size of seven floats
		std::cout << *((float*)((char*)m.data() + sizeof(float) * 8)) << std::endl; // Access z.z by taking the address of x + the size of eight floats

		return 0;
	}

Result:

.. code-block::

	1
	2
	3
	4
	5
	6
	7
	8
	9