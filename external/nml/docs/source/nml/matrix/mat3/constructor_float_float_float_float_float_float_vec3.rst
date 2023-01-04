:orphan:

mat3: mat3(float _xx, float _xy, float _xz, float _yx, float _yy, float _yz, nml::vec3 _zxzyzz)
===============================================================================================

Construct a ([*_xx*, *_xy*, *_xz*], [*_yx*, *_yy*, *_yz*], [*_zxzyzz.x*, *_zxzyzz.y*, *_zxzyzz.z*]) matrix.

:math:`\begin{bmatrix} \_xx & \_yx & \_zxzyzz.x \\ \_xy & \_yy & \_zxzyzz.y \\ \_xz & \_yz & \_zxzyzz.z \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat3.h"
	#include <iostream>

	int main() {
		nml::mat3 m(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, nml::vec3(7.0f, 8.0f, 9.0f));
		std::cout << nml::to_string(m) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[1.000000, 2.000000, 3.000000], [4.000000, 5.000000, 6.000000], [7.000000, 8.000000, 9.000000]]