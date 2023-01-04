:orphan:

mat3: nml::mat3& operator[](size_t index)
=========================================

Return a reference to *x* if index is 0, a reference to *y* if index is 1 or a reference to *z* if index is 2, else, throw an exception.

Example
-------

.. code-block:: cpp

	#include "include/mat3.h"
	#include <iostream>

	int main() {
		nml::mat3 m(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
		m[0] = nml::vec3(5.0f, 6.0f, 7.0f);
		m[1][1] = 12.0f;
		m[2][2] = 25.0f;
		std::cout << nml::to_string(m) << std::endl;
		m[3][0] = 2.0; // Error

		return 0;
	}

Result:

.. code-block::

	[[5.000000, 6.000000, 7.000000], [4.000000, 12.000000, 6.000000], [7.000000, 8.000000, 25.000000]]
	terminate called after throwing an instance of 'std::out_of_range'
		what():  mat3::operator[]: index is out of range.
	Aborted