:orphan:

std::string nml::to_string(const nml::vec3& vec)
================================================

Return a *vec3* as a string under the format “[*x*, *y*, *z*]”.

Example
-------

.. code-block:: cpp

	#include "include/vec3.h"
	#include <iostream>

	int main() {
		nml::vec3 v(1.0f, 2.0f, 3.0f);
		std::cout << nml::to_string(v) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[1.000000, 2.000000, 3.000000]