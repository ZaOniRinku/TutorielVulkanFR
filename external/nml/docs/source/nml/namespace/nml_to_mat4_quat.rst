:orphan:

nml::mat4 nml::to_mat4(const nml::quat& qua)
============================================

Return a 3D rotation matrix from a quaternion.

The conversion from quaternion to a *mat4* rotation matrix is calculated this way:

:math:`\begin{bmatrix} a & d & g & 0.0 \\ b & e & h & 0.0 \\ c & f & i & 0.0 \\ 0.0 & 0.0 & 0.0 & 1.0 \end{bmatrix}`

:math:`a = 1.0 - 2.0 * (qua.c^2 + qua.d^2)`
:math:`b = 2.0 * (qua.b * qua.c - qua.a * qua.d)`
:math:`c = 2.0 * (qua.b * qua.d + qua.a * qua.c)`
:math:`d = 2.0 * (qua.b * qua.c + qua.a * qua.d)`
:math:`e = 1.0 - 2.0 * (qua.b^2 + qua.d^2)`
:math:`f = 2.0 * (qua.c * qua.d - qua.a * qua.b)`
:math:`g = 2.0 * (qua.b * qua.d - qua.a * qua.c)`
:math:`h = 1.0 - 2.0 * (qua.b^2 + qua.d^2)`
:math:`i = 1.0 - 2.0 * (qua.b^2 + qua.c^2)`

Example
-------

.. code-block:: cpp

	#include "include/mat4.h"
	#include "include/quat.h"
	#include <iostream>

	int main() {
		nml::quat q(1.0f, 1.0f, 1.0f, 1.0f);
		q = nml::normalize(q);
		nml::mat4 m = nml::to_mat4(q);
		std::cout << nml::to_string(m) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[0.000000, 1.000000, 0.000000, 0.000000], [0.000000, 0.000000, 1.000000, 0.000000], [1.000000, 0.000000, 0.000000, 0.000000], [0.000000, 0.000000, 0.000000, 1.000000]]