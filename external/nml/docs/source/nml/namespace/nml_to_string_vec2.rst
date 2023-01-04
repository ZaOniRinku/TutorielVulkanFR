:orphan:

std::string nml::to_string(const nml::vec2& vec)
================================================

Return a *vec2* as a string under the format “[*x*, *y*]”.

Example
-------

.. code-block:: cpp

	#include "include/vec2.h"
	#include <iostream>

	int main() {
		nml::vec2 v(1.0f, 2.0f);
		std::cout << nml::to_string(v) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[1.000000, 2.000000]