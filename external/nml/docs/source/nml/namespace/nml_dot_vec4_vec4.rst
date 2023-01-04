:orphan:

float nml::dot(const nml::vec4& a, const nml::vec4& b)
======================================================

Return the dot product between two *vec4*.

The dot product of two *vec4* is calculated this way:
	
:math:`\begin{bmatrix} a.x \\ a.y \\ a.z \\ a.w \end{bmatrix} \cdot \begin{bmatrix} b.x \\ b.y \\ b.z \\ b.w \end{bmatrix} = (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w)`

Example
-------

.. code-block:: cpp

	#include "include/vec4.h"
	#include <iostream>

	int main() {
		nml::vec4 a(2.0f, -2.0f, 1.0f, 0.0f);
		nml::vec4 b(0.0f, 1.0f, 0.0f, 0.0f);
		float c = nml::dot(a, b);
		std::cout << c << std::endl;

		return 0;
	}

Result:

.. code-block::

	-2