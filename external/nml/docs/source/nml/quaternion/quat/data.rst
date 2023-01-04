:orphan:

quat: float* data()
===================

Return a pointer to the quaternion's elements.

Example
-------

.. code-block:: cpp

	#include "include/quat.h"
	#include <iostream>

	int main() {
		nml::quat q(1.0f, 0.25f, 0.5f, 0.75f);
		std::cout << *q.data() << std::endl; // Access a
		std::cout << *((float*)((char*)q.data() + sizeof(float))) << std::endl; // Access b by taking the address of x + the size of a float
		std::cout << *((float*)((char*)q.data() + sizeof(float) * 2)) << std::endl; // Access c by taking the address of x + the size of two floats
		std::cout << *((float*)((char*)q.data() + sizeof(float) * 3)) << std::endl; // Access d by taking the address of x + the size of three floats

		return 0;
	}

Result:

.. code-block::

	1
	0.25
	0.5
	0.75