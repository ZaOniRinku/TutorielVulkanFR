:orphan:

nml::quat nml::normalize(const nml::quat& qua)
==============================================

Return a *quat* with the same direction as *qua* but with length 1.

The normalization of a *quat* is calculated this way:
	
:math:`norm(qua.a + qua.bi + qua.cj + qua.dk) =`

:math:`(\frac{qua.a}{\left \| qua \right \|}) + (\frac{qua.b}{\left \| qua \right \|})i + (\frac{qua.c}{\left \| qua \right \|})j + (\frac{qua.d}{\left \| qua \right \|})k`

Example
-------

.. code-block:: cpp

	#include "include/quat.h"
	#include <iostream>

	int main() {
		nml::quat a(1.0f, 0.25f, 0.5f, 0.75f);
		std::cout << a.length() << std::endl;
		nml::quat b = nml::normalize(a);
		std::cout << nml::to_string(b) << std::endl;
		std::cout << b.length() << std::endl;

		return 0;
	}

Result:

.. code-block::

	1.36931
	0.730297 + 0.182574i + 0.365148j + 0.547723k
	1