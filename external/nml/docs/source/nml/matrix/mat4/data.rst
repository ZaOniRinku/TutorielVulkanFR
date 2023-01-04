:orphan:

mat4: float* data()
===================

Return a pointer to the matrix's elements.

Example
-------

.. code-block:: cpp

	#include "include/mat4.h"
	#include <iostream>

	int main() {
		nml::mat4 m(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
		std::cout << *m.data() << std::endl; // Access x.x
		std::cout << *((float*)((char*)m.data() + sizeof(float))) << std::endl; // Access x.y by taking the address of x + the size of a float
		std::cout << *((float*)((char*)m.data() + sizeof(float) * 2)) << std::endl; // Access x.z by taking the address of x + the size of two floats
		std::cout << *((float*)((char*)m.data() + sizeof(float) * 3)) << std::endl; // Access x.w by taking the address of x + the size of three floats
		std::cout << *((float*)((char*)m.data() + sizeof(float) * 4)) << std::endl; // Access y.x by taking the address of x + the size of four floats
		std::cout << *((float*)((char*)m.data() + sizeof(float) * 5)) << std::endl; // Access y.y by taking the address of x + the size of five floats
		std::cout << *((float*)((char*)m.data() + sizeof(float) * 6)) << std::endl; // Access y.z by taking the address of x + the size of six floats
		std::cout << *((float*)((char*)m.data() + sizeof(float) * 7)) << std::endl; // Access y.w by taking the address of x + the size of seven floats
		std::cout << *((float*)((char*)m.data() + sizeof(float) * 8)) << std::endl; // Access z.x by taking the address of x + the size of eight floats
		std::cout << *((float*)((char*)m.data() + sizeof(float) * 9)) << std::endl; // Access z.y by taking the address of x + the size of nine floats
		std::cout << *((float*)((char*)m.data() + sizeof(float) * 10)) << std::endl; // Access z.z by taking the address of x + the size of ten floats
		std::cout << *((float*)((char*)m.data() + sizeof(float) * 11)) << std::endl; // Access z.w by taking the address of x + the size of eleven floats
		std::cout << *((float*)((char*)m.data() + sizeof(float) * 12)) << std::endl; // Access w.x by taking the address of x + the size of twelve floats
		std::cout << *((float*)((char*)m.data() + sizeof(float) * 13)) << std::endl; // Access w.y by taking the address of x + the size of thirteen floats
		std::cout << *((float*)((char*)m.data() + sizeof(float) * 14)) << std::endl; // Access w.z by taking the address of x + the size of fourteen floats
		std::cout << *((float*)((char*)m.data() + sizeof(float) * 15)) << std::endl; // Access w.w by taking the address of x + the size of fifteen floats

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
	10
	11
	12
	13
	14
	15
	16