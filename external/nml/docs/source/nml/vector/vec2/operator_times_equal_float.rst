:orphan:

vec2: nml::vec2& operator*=(const float other)
==============================================

Multiply the current *vec2* by a scalar.

The product between a *vec2* and a scalar is calculated this way:

:math:`\begin{bmatrix} x \\ y \end{bmatrix} * other = \begin{bmatrix} x * other \\ y * other \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec2.h"
	#include <iostream>

	int main() {
		nml::vec2 v(1.0f, 2.0f);
		v *= 2.0f;
		std::cout << nml::to_string(v) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[2.000000, 4.000000]