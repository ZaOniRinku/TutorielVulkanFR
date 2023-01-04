:orphan:

nml::mat4 translate(const nml::vec3& translation)
=================================================

Return a 3D translation matrix according to the translation vector.

The 3D translation matrix is calculated this way:

:math:`\begin{bmatrix} 1.0 & 0.0 & 0.0 & translation.x \\ 0.0 & 1.0 & 0.0 & translation.y \\ 0.0 & 0.0 & 1.0 & translation.z \\ 0.0 & 0.0 & 0.0 & 1.0 \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat4.h"
	#include "include/vec3.h"
	#include <iostream>

	int main() {
		nml::vec3 translationVector(1.0f, 2.0f, 3.0f);
		nml::mat4 m = nml::translate(translationVector);
		std::cout << nml::to_string(m) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[1.000000, 0.000000, 0.000000, 0.000000], [0.000000, 1.000000, 0.000000, 0.000000], [0.000000, 0.000000, 1.000000, 0.000000], [1.000000, 2.000000, 3.000000, 1.000000]]