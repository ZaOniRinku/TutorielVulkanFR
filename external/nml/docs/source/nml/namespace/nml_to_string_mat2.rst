:orphan:

std::string nml::to_string(const nml::mat2& vec)
================================================

Return a *mat2* as a string under the format “[[*x.x*, *x.y*], [*y.x*, *y.y*]]”.

Example
-------

.. code-block:: cpp

	#include "include/mat2.h"
	#include <iostream>

	int main() {
		nml::mat2 m(1.0f, 2.0f, 3.0f, 4.0f);
		std::cout << nml::to_string(m) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[1.000000, 2.000000], [3.000000, 4.000000]]