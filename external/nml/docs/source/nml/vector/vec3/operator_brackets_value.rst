:orphan:

vec3: const float operator[](size_t index) const
================================================

Return the value of *x* if index is 0, the value of *y* if index is 1 or the value to *z* if index is 2, else, throw an exception.

Example
-------

.. code-block:: cpp

	#include "include/vec3.h"
	#include <iostream>

	int main() {
		nml::vec3 v(1.0f, 2.0f, 3.0f);
		float a = v[0];
		float b = v[1];
		float c = v[2];
		std::cout << a << ", " << b << ", " << c << std::endl;
		float d = v[3]; // Error

		return 0;
	}

Result:

.. code-block::

	1, 2, 3
	terminate called after throwing an instance of 'std::out_of_range'
		what():  vec3::operator[]: index is out of range.
	Aborted