:orphan:

vec3: float& operator[](size_t index)
=====================================

Return a reference to *x* if index is 0, a reference to *y* if index is 1 or a reference to *z* if index is 2, else, throw an exception.

Example
-------

.. code-block:: cpp

	#include "include/vec3.h"
	#include <iostream>

	int main() {
		nml::vec3 v(1.0f, 2.0f, 3.0f);
		v[0] = 3.0f;
		v[1] = 1.0f;
		v[2] = 4.0f;
		std::cout << nml::to_string(v) << std::endl;
		v[3] = 2.0; // Error

		return 0;
	}

Result:

.. code-block::

	[3.000000, 1.000000, 4.000000]
	terminate called after throwing an instance of 'std::out_of_range'
		what():  vec3::operator[]: index is out of range.
	Aborted