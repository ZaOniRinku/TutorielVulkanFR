:orphan:

vec3: nml::vec3& operator-=(const nml::vec3& other)
===================================================

Substract a *vec3* from the current *vec3*.

The difference between two *vec3* is calculated this way:

:math:`\begin{bmatrix} x \\ y \\ z \end{bmatrix} - \begin{bmatrix} other.x \\ other.y \\ other.z \end{bmatrix} = \begin{bmatrix} x - other.x \\ y - other.y \\ z - other.z \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec3.h"
	#include <iostream>

	int main() {
		nml::vec3 a(4.0f, 6.0f, 8.0f);
		nml::vec3 b(3.0f, 4.0f, 5.0f);
		a -= b;
		std::cout << nml::to_string(a) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[1.000000, 2.000000, 3.000000]