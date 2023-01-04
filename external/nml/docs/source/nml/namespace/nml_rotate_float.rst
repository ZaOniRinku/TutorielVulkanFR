:orphan:

nml::mat3 rotate(const float angle)
===================================

Return a 2D rotation matrix according to the angle (in radians).

The 2D rotation matrix is calculated this way:

:math:`\begin{bmatrix} \cos(angle) & -\sin(angle) & 0.0 \\ \sin(angle) & \cos(angle) & 0.0 \\ 0.0 & 0.0 & 1.0 \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat3.h"
	#include <iostream>

	int main() {
		const float pi = 3.14159265358979323846f;
		float rotationAngle = pi / 2.0f; // 90°
		nml::mat3 m = nml::rotate(rotationAngle);
		std::cout << nml::to_string(m) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[-0.000000, 1.000000, 0.000000], [-1.000000, -0.000000, 0.000000], [0.000000, 0.000000, 1.000000]]