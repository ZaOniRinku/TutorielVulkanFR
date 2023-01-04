:orphan:

vec2: const float operator[](size_t index) const
================================================

Return the value of *x* if index is 0 or the value of *y* if index is 1, else, throw an exception.

Example
-------

.. code-block:: cpp

	#include "include/vec2.h"
	#include <iostream>

	int main() {
		nml::vec2 v(1.0f, 2.0f);
		float a = v[0];
		float b = v[1];
		std::cout << a << ", " << b << std::endl;
		float c = v[2]; // Error

		return 0;
	}

Result:

.. code-block::

	1, 2
	terminate called after throwing an instance of 'std::out_of_range'
  		what():  vec2::operator[]: index is out of range.
	Aborted