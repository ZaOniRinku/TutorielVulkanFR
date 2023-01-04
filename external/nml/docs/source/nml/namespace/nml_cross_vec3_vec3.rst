:orphan:

nml::vec3 nml::cross(const nml::vec3& a, const nml::vec3& b)
============================================================

Return the dot product between two *vec3*.

The dot product of two *vec3* is calculated this way:

:math:`\begin{bmatrix} a.x \\ a.y \\ a.z \end{bmatrix} \times \begin{bmatrix} b.x \\ b.y \\ b.z \end{bmatrix} = \begin{bmatrix} a.y * b.z - a.z * b.y \\ a.z * b.x - a.x * b.z \\ a.x * b.y - a.y * b.x \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec3.h"
	#include <iostream>

	int main() {
		nml::vec3 a(1.0f, 2.0f, 3.0f);
		nml::vec3 b(4.0f, 5.0f, 6.0f);
		nml::vec3 c = nml::cross(a, b);
		std::cout << nml::to_string(c) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[-3.000000, 6.000000, -3.000000]