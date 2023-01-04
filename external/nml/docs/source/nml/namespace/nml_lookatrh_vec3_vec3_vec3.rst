:orphan:

nml::mat4 lookAtRH(const nml::vec3& from, const nml::vec3& to, const nml::vec3& up)
===================================================================================

Return a right-hand look at view matrix.

The right-hand look at view matrix is calculated this way:

:math:`\begin{bmatrix} right.x & right.y & right.z & -(right \cdot from) \\ realUp.x & realUp.y & realUp.z & -(realUp \cdot from) \\ -forward.x & -forward.y & -forward.z & forward \cdot from \\ 0.0 & 0.0 & 0.0 & 1.0 \end{bmatrix}`

:math:`forward = norm(to - from)`

:math:`right = norm(forward \times up)`

:math:`realUp = right \times forward`

Example
-------

.. code-block:: cpp

	#include "../nml/include/mat4.h"
	#include "../nml/include/vec3.h"
	#include <iostream>

	int main() {
		nml::mat4 m = nml::lookAtRH(nml::vec3(2.5f, 3.0f, 4.5f), nml::vec3(5.0f, 1.25f, 2.0f), nml::vec3(0.0f, 1.0f, 0.0f));
		std::cout << nml::to_string(m) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[0.707107, 0.313677, -0.633724, 0.000000], [-0.000000, 0.896221, 0.443607, 0.000000], [0.707107, -0.313677, 0.633724, 0.000000], [-4.949747, -2.061309, -2.598269, 1.000000]]