:orphan:

vec2: float& operator[](size_t index)
=====================================

Return a reference to *x* if index is 0 or a reference to *y* if index is 1, else, throw an exception.

Example
-------

.. code-block:: cpp

	#include "include/vec2.h"
	#include <iostream>

	int main() {
		nml::vec2 v(1.0f, 2.0f);
		v[0] = 3.0f;
		v[1] = 1.0f;
		std::cout << nml::to_string(v) << std::endl;
		v[2] = 2.0; // Error

		return 0;
	}

Result:

.. code-block::

	[3.000000, 1.000000]
	terminate called after throwing an instance of 'std::out_of_range'
		what():  vec2::operator[]: index is out of range.
	Aborted