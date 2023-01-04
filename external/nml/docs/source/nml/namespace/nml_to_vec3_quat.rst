:orphan:

nml::vec3 nml::to_vec3(const nml::quat& qua)
============================================

Return a *vec3* representing euler angles in radians from a quaternion.

The conversion from quaternion to euler angles is calculated this way:

:math:`\small \begin{bmatrix} atan2(2.0 * (qua.a * qua.b + qua.c * qua.d), 1.0 - (2.0 * (qua.b^2 + qua.c^2))) \\ asin(2.0 * (qua.a * qua.c - qua.d * qua.b)) \\ atan2(2.0 * (qua.a * qua.d + qua.b * qua.c), 1.0 - (2.0 * (qua.c^2 + qua.d^2))) \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec3.h"
	#include "include/quat.h"
	#include <iostream>

	int main() {
		nml::quat q(1.0f, 1.0f, 1.0f, 1.0f);
		q = nml::normalize(q);
		nml::vec3 v = nml::to_vec3(q);
		std::cout << nml::to_string(v) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[1.570796, 0.000000, 1.570796]