:orphan:

nml::mat4 scale(const nml::vec3& scaling)
=========================================

Return a 3D scaling matrix according to the scaling factors.

The 3D scaling matrix is calculated this way:

:math:`\begin{bmatrix} scaling.x & 0.0 & 0.0 & 0.0 \\ 0.0 & scaling.y & 0.0 & 0.0 \\ 0.0 & 0.0 & scaling.z & 0.0 \\ 0.0 & 0.0 & 0.0 & 1.0 \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat4.h"
	#include "include/vec3.h"
	#include <iostream>

	int main() {
		nml::vec3 scaling(2.0f, 2.0f, 2.0f);
		nml::mat4 m = nml::scale(scaling);
		std::cout << nml::to_string(m) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[2.000000, 0.000000, 0.000000, 0.000000], [0.000000, 2.000000, 0.000000, 0.000000], [0.000000, 0.000000, 2.000000, 0.000000], [0.000000, 0.000000, 0.000000, 1.000000]]