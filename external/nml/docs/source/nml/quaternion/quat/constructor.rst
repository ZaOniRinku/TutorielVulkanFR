:orphan:

quat: quat()
============

Construct a (1.0, 0.0, 0.0, 0.0) identity quaternion.

:math:`1.0 + 0.0i + 0.0j + 0.0k`

Example
-------

.. code-block:: cpp

	#include "include/quat.h"
	#include <iostream>

	int main() {
		nml::quat q;
		std::cout << nml::to_string(q) << std::endl;

		return 0;
	}

Result:

.. code-block::

	1.000000 + 0.000000i + 0.000000j + 0.000000k