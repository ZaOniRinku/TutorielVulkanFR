:orphan:

mat3: const nml::mat3& operator[](size_t index) const
=====================================================

Return a const reference to *x* if index is 0, a const reference to *y* if index is 1 or a const reference to *z* if index is 2, else, throw an exception.

Example
-------

.. code-block:: cpp

	#include "include/mat3.h"
	#include <iostream>

	int main() {
		nml::mat3 m(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
		nml::vec3 a = m[0];
		float b = m[1][2];
		float c = m[2][1];
		std::cout << nml::to_string(a) << ", " << b << ", " << c << std::endl;
		nml::vec3 d = m[3]; // Error

		return 0;
	}

Result:

.. code-block::

	[1.000000, 2.000000, 3.000000], 6, 8
	terminate called after throwing an instance of 'std::out_of_range'
		what():  mat3::operator[]: index is out of range.
	Aborted