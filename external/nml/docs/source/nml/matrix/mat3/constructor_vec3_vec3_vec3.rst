:orphan:

mat3: mat3(nml::vec3 _xxxyxz, nml::vec3 _yxyyyz, nml::vec3 _zxzyzz)
===================================================================

Construct a ([*_xxxyxz.x*, *_xxxyxz.y*, *_xxxyxz.z*], [*_yxyyyz.x*, *_yxyyyz.y*, *_yxyyyz.z*], [*_zxzyzz.x*, *_zxzyzz.y*, *_zxzyzz.z*]) matrix.

:math:`\begin{bmatrix} \_xxxyxz.x & \_yxyyyz.x & \_zxzyzz.x \\ \_xxxyxz.y & \_yxyyyz.y & \_zxzyzz.y \\ \_xxxyxz.z & \_yxyyyz.z & \_zxzyzz.z \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat3.h"
	#include <iostream>

	int main() {
		nml::mat3 m(nml::vec3(1.0f, 2.0f, 3.0f), nml::vec3(4.0f, 5.0f, 6.0f), nml::vec3(7.0f, 8.0f, 9.0f));
		std::cout << nml::to_string(m) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[1.000000, 2.000000, 3.000000], [4.000000, 5.000000, 6.000000], [7.000000, 8.000000, 9.000000]]