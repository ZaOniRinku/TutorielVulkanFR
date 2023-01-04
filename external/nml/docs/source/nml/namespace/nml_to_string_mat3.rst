:orphan:

std::string nml::to_string(const nml::mat3& vec)
================================================

Return a *mat3* as a string under the format “[[*x.x*, *x.y*, *x.z*], [*y.x*, *y.y*, *y.z*], [*z.x*, *z.y*, *z.z*]]”.

Example
-------

.. code-block:: cpp

	#include "include/mat3.h"
	#include <iostream>

	int main() {
		nml::mat3 m(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
		std::cout << nml::to_string(m) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[1.000000, 2.000000, 3.000000], [4.000000, 5.000000, 6.000000], [7.000000, 8.000000, 9.000000]]