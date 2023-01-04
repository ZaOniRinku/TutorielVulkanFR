:orphan:

mat4: nml::mat4& operator[](size_t index)
=========================================

Return a reference to *x* if index is 0, a reference to *y* if index is 1, a reference to *z* if index is 2 or a reference to *w* if index is 3 else, throw an exception.

Example
-------

.. code-block:: cpp

	#include "include/mat4.h"
	#include <iostream>

	int main() {
		nml::mat4 m(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
		m[0] = nml::vec4(5.0f, 6.0f, 7.0f, 20.0f);
		m[1][1] = 12.0f;
		m[2][2] = 25.0f;
		m[3][3] = 250.0f;
		std::cout << nml::to_string(m) << std::endl;
		m[4][0] = 2.0; // Error

		return 0;
	}

Result:

.. code-block::

	[[5.000000, 6.000000, 7.000000, 20.000000], [5.000000, 12.000000, 7.000000, 8.000000], [9.000000, 10.000000, 25.000000, 12.000000], [13.000000, 14.000000, 15.000000, 250.000000]]
	terminate called after throwing an instance of 'std::out_of_range'
		what():  mat4::operator[]: index is out of range.
	Aborted