:orphan:

vec3: nml::vec3& operator*=(const float other)
==============================================

Multiply the current *vec3* by a scalar.

The product between a *vec3* and a scalar is calculated this way:

:math:`\begin{bmatrix} x \\ y \\ z \end{bmatrix} * other = \begin{bmatrix} x * other \\ y * other \\ z * other \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec3.h"
	#include <iostream>

	int main() {
		nml::vec3 v(1.0f, 2.0f, 3.0f);
		v *= 2.0f;
		std::cout << nml::to_string(v) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[2.000000, 4.000000, 6.000000]