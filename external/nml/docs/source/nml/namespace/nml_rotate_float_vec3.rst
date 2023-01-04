:orphan:

nml::mat4 rotate(const float angle, const nml::vec3& axis)
==========================================================

Return a 3D rotation matrix according to the angle (in radians) and the axis. *axis* should be normalized.

The 3D rotation matrix is calculated this way:

:math:`\begin{bmatrix} a & d & g & 0.0 \\ b & e & h & 0.0 \\ c & f & i & 0.0 \\ 0.0 & 0.0 & 0.0 & 1.0 \end{bmatrix}`

:math:`a = \cos(angle) + (axis.x * axis.x * (1.0 - \cos(angle)))`
:math:`b = (axis.y * axis.x * (1.0 - \cos(angle))) + axis.z * \sin(angle)`
:math:`c = (axis.z * axis.x * (1.0 - \cos(angle))) - axis.y * \sin(angle)`
:math:`d = (axis.x * axis.y * (1.0 - \cos(angle))) - axis.z * \sin(angle)`
:math:`e = \cos(angle) + (axis.y * axis.y * (1.0 - \cos(angle)))`
:math:`f = (axis.z * axis.y * (1.0 - \cos(angle))) + axis.x * \sin(angle)`
:math:`g = (axis.x * axis.z * (1.0 - \cos(angle))) + axis.y * \sin(angle)`
:math:`h = (axis.y * axis.z * (1.0 - \cos(angle))) - axis.x * \sin(angle)`
:math:`i = \cos(angle) + (axis.z * axis.z * (1.0 - \cos(angle)))`

**The rotate function does not normalize the vector axis.**

Example
-------

.. code-block:: cpp

	#include "include/mat4.h"
	#include "include/vec3.h"
	#include <iostream>

	int main() {
		const float pi = 3.14159265358979323846f;
		float rotationAngle = pi / 2.0f; // 90°
		nml::vec3 axis(0.0f, 1.0f, 0.0f);
		nml::mat4 m = nml::rotate(rotationAngle, axis);
		std::cout << nml::to_string(m) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[-0.000000, 0.000000, -1.000000, 0.000000], [0.000000, 1.000000, 0.000000, 0.000000], [1.000000, 0.000000, -0.000000, 0.000000], [0.000000, 0.000000, 0.000000, 1.000000]]