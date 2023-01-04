:orphan:

std::string nml::to_string(const nml::mat4& vec)
================================================

Return a *mat4* as a string under the format “[[*x.x*, *x.y*, *x.z*, *x.w*], [*y.x*, *y.y*, *y.z*, *y.w*], [*z.x*, *z.y*, *z.z*, *z.w*], [*w.x*, *w.y*, *w.z*, *w.w*]]”.

Example
-------

.. code-block:: cpp

	#include "include/mat4.h"
	#include <iostream>

	int main() {
		nml::mat4 m(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
		std::cout << nml::to_string(m) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[1.000000, 2.000000, 3.000000, 4.000000], [5.000000, 6.000000, 7.000000, 8.000000], [9.000000, 10.000000, 11.000000, 12.000000], [13.000000, 14.000000, 15.000000, 16.000000]]