:orphan:

float nml::dot(const nml::vec2& a, const nml::vec2& b)
======================================================

Return the dot product between two *vec2*.

The dot product of two *vec2* is calculated this way:

:math:`\begin{bmatrix} a.x \\ a.y \end{bmatrix} \cdot \begin{bmatrix} b.x \\ b.y \end{bmatrix} = (a.x * b.x) + (a.y * b.y)`

Example
-------

.. code-block:: cpp

	#include "include/vec2.h"
	#include <iostream>

	int main() {
		nml::vec2 a(2.0f, -2.0f);
		nml::vec2 b(0.0f, 1.0f);
		float c = nml::dot(a, b);
		std::cout << c << std::endl;

		return 0;
	}

Result:

.. code-block::

	-2