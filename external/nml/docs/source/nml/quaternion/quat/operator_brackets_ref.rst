:orphan:

quat: float& operator[](size_t index)
=====================================

Return a reference to *a* if index is 0, a reference to *b* if index is 1, a reference to *c* if index is 2 or a reference to *d* if index is 3, else, throw an exception.

Example
-------

.. code-block:: cpp

	#include "include/quat.h"
	#include <iostream>

	int main() {
		nml::quat q(1.0f, 0.25f, 0.5f, 0.75f);
		q[0] = 3.0f;
		q[1] = 1.0f;
		q[2] = 4.0f;
		q[3] = 2.0f;
		std::cout << nml::to_string(q) << std::endl;
		q[4] = 5.0; // Error

		return 0;
	}

Result:

.. code-block::

	3.000000 + 1.000000i + 4.000000j + 2.000000k
	terminate called after throwing an instance of 'std::out_of_range'
		what():  quat::operator[]: index is out of range.
	Aborted