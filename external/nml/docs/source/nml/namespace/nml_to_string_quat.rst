:orphan:

std::string nml::to_string(const nml::quat& vec)
================================================

Return a *quat* as a string under the format “*a* + *b*\i + *c*\j + *d*\k”.

Example
-------

.. code-block:: cpp

	#include "include/quat.h"
	#include <iostream>

	int main() {
		nml::quat q(1.0f, 0.25f, 0.5f, 0.75f);
		std::cout << nml::to_string(q) << std::endl;

		return 0;
	}

Result:

.. code-block::

	1.000000 + 0.250000i + 0.500000j + 0.750000k