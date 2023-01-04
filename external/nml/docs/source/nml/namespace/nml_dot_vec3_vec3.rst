:orphan:

float nml::dot(const nml::vec3& a, const nml::vec3& b)
======================================================

Return the dot product between two *vec3*.

The dot product of two *vec3* is calculated this way:

:math:`\begin{bmatrix} a.x \\ a.y \\ a.z \end{bmatrix} \cdot \begin{bmatrix} b.x \\ b.y \\ b.z \end{bmatrix} = (a.x * b.x) + (a.y * b.y) + (a.z * b.z)`

Example
-------

.. code-block:: cpp

	#include "include/vec3.h"
	#include <iostream>

	int main() {
		nml::vec3 a(2.0f, -2.0f, 1.0f);
		nml::vec3 b(0.0f, 1.0f, 0.0f);
		float c = nml::dot(a, b);
		std::cout << c << std::endl;

		return 0;
	}

Result:

.. code-block::

	-2