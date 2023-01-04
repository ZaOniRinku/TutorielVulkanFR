:orphan:

mat4: const nml::mat4& operator[](size_t index) const
=====================================================

Return a const reference to *x* if index is 0, a const reference to *y* if index is 1, a const reference to *z* if index is 2 or a const reference to *w* if index is 3 else, throw an exception.

Example
-------

.. code-block:: cpp

	#include "include/mat4.h"
	#include <iostream>

	int main() {
		nml::mat4 m(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
		nml::vec4 a = m[0];
		float b = m[1][2];
		float c = m[2][1];
		float d = m[3][3];
		std::cout << nml::to_string(a) << ", " << b << ", " << c << ", " << d << std::endl;
		nml::vec4 e = m[4]; // Error

		return 0;
	}

Result:

.. code-block::

	[1.000000, 2.000000, 3.000000, 4.000000], 7, 10, 16
	terminate called after throwing an instance of 'std::out_of_range'
		what():  mat4::operator[]: index is out of range.
	Aborted