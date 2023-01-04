:orphan:

quat: const float operator[](size_t index) const
================================================

Return the value of *a* if index is 0, the value of *b* if index is 1, the value of *c* if index is 2 or the value of *d* if index is 3, else, throw an exception.

Example
-------

.. code-block:: cpp

	#include "include/quat.h"
	#include <iostream>

	int main() {
		nml::quat q(1.0f, 0.25f, 0.5f, 0.75f);
		float a = q[0];
		float b = q[1];
		float c = q[2];
		float d = q[3];
		std::cout << a << ", " << b << ", " << c << ", " << d << std::endl;
		float e = q[4]; // Error

		return 0;
	}

Result:

.. code-block::

	1, 0.25, 0.5, 0.75
	terminate called after throwing an instance of 'std::out_of_range'
		what():  quat::operator[]: index is out of range.
	Aborted