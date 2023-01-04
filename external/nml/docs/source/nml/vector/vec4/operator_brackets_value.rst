:orphan:

vec4: const float operator[](size_t index) const
================================================

Return the value of *x* if index is 0, the value of *y* if index is 1, the value of *z* if index is 2 or the value of *w* if index is 3, else, throw an exception.

Example
-------

.. code-block:: cpp

	#include "include/vec4.h"
	#include <iostream>

	int main() {
		nml::vec4 v(1.0f, 2.0f, 3.0f, 4.0f);
		float a = v[0];
		float b = v[1];
		float c = v[2];
		float d = v[3];
		std::cout << a << ", " << b << ", " << c << ", " << d << std::endl;
		float e = v[4]; // Error

		return 0;
	}

Result:

.. code-block::

	1, 2, 3, 4
	terminate called after throwing an instance of 'std::out_of_range'
		what():  vec4::operator[]: index is out of range.
	Aborted