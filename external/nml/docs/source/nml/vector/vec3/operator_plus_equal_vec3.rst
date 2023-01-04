:orphan:

vec3: nml::vec3& operator+=(const nml::vec3& other)
===================================================

Add a *vec3* to the current *vec3*.

The sum between two *vec3* is calculated this way:

:math:`\begin{bmatrix} x \\ y \\ z \end{bmatrix} + \begin{bmatrix} other.x \\ other.y \\ other.z \end{bmatrix} = \begin{bmatrix} x + other.x \\ y + other.y \\ z + other.z \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec3.h"
	#include <iostream>

	int main() {
		nml::vec3 a(1.0f, 2.0f, 4.0f);
		nml::vec3 b(3.0f, 4.0f, 5.0f);
		a += b;
		std::cout << nml::to_string(a) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[4.000000, 6.000000, 9.000000]