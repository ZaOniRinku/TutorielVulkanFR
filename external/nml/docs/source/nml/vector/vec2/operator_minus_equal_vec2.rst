:orphan:

vec2: nml::vec2& operator-=(const nml::vec2& other)
===================================================

Substract a *vec2* from the current *vec2*.

The difference between two *vec2* is calculated this way:

:math:`\begin{bmatrix} x \\ y \end{bmatrix} - \begin{bmatrix} other.x \\ other.y \end{bmatrix} = \begin{bmatrix} x - other.x \\ y - other.y \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec2.h"
	#include <iostream>

	int main() {
		nml::vec2 a(4.0f, 6.0f);
		nml::vec2 b(3.0f, 4.0f);
		a -= b;
		std::cout << nml::to_string(a) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[1.000000, 2.000000]