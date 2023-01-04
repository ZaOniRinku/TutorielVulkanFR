:orphan:

vec2: nml::vec2& operator+=(const nml::vec2& other)
===================================================

Add a *vec2* to the current *vec2*.

The sum between two *vec2* is calculated this way:

:math:`\begin{bmatrix} x \\ y \end{bmatrix} + \begin{bmatrix} other.x \\ other.y \end{bmatrix} = \begin{bmatrix} x + other.x \\ y + other.y \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec2.h"
	#include <iostream>

	int main() {
		nml::vec2 a(1.0f, 2.0f);
		nml::vec2 b(3.0f, 4.0f);
		a += b;
		std::cout << nml::to_string(a) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[4.000000, 6.000000]