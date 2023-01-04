:orphan:

mat2: nml::mat2& operator[](size_t index)
=========================================

Return a reference to *x* if index is 0 or a reference to *y* if index is 1, else, throw an exception.

Example
-------

.. code-block:: cpp

	#include "include/mat2.h"
	#include <iostream>

	int main() {
		nml::mat2 m(1.0f, 2.0f, 3.0f, 4.0f);
		m[0] = nml::vec2(5.0f, 6.0f);
		m[1][1] = 7.0f;
		std::cout << nml::to_string(m) << std::endl;
		m[2][0] = 2.0; // Error

		return 0;
	}

Result:

.. code-block::

	[[5.000000, 6.000000], [3.000000, 7.000000]]
	terminate called after throwing an instance of 'std::out_of_range'
		what():  mat2::operator[]: index is out of range.
	Aborted