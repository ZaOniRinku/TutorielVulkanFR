:orphan:

mat2: const nml::mat2& operator[](size_t index) const
=====================================================

Return a const reference to *x* if index is 0 or a const reference to *y* if index is 1, else, throw an exception.

Example
-------

.. code-block:: cpp

	#include "include/mat2.h"
	#include <iostream>

	int main() {
		nml::mat2 m(1.0f, 2.0f, 3.0f, 4.0f);
		nml::vec2 a = m[0];
		float b = m[1][0];
		float c = m[1][1];
		std::cout << nml::to_string(a) << ", " << b << ", " << c << std::endl;
		nml::vec2 d = m[2]; // Error

		return 0;
	}

Result:

.. code-block::

	[1.000000, 2.000000], 3, 4
	terminate called after throwing an instance of 'std::out_of_range'
		what():  mat2::operator[]: index is out of range.
	Aborted