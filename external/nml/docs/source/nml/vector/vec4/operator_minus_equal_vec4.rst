:orphan:

vec4: nml::vec4& operator-=(const nml::vec4& other)
===================================================

Substract a *v*ec4* from the current *vec4*.

The difference between two *vec4* is calculated this way:

:math:`\begin{bmatrix} x \\ y \\ z \\ w \end{bmatrix} - \begin{bmatrix} other.x \\ other.y \\ other.z \\ other.w \end{bmatrix} = \begin{bmatrix} x - other.x \\ y - other.y \\ z - other.z \\ w - other.w \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec4.h"
	#include <iostream>

	int main() {
		nml::vec4 a(4.0f, 6.0f, 8.0f, 10.0f);
		nml::vec4 b(3.0f, 4.0f, 5.0f, 6.0f);
		a -= b;
		std::cout << nml::to_string(a) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[1.000000, 2.000000, 3.000000, 4.000000]