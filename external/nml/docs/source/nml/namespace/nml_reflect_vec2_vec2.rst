:orphan:

nml::vec2 nml::reflect(const nml::vec2& i, const nml::vec2& n)
=========================================================================

Return the reflected direction between the incident vector *i* and the normal *n*. *n* should be normalized.

The reflected direction between the incident vector *i* and the normal *n* is calculated this way:

:math:`\begin{bmatrix} i.x \\ i.y \end{bmatrix} - 2.0 * (\begin{bmatrix} n.x \\ n.y \end{bmatrix} \cdot \begin{bmatrix} i.x \\ i.y \end{bmatrix}) * \begin{bmatrix} n.x \\ n.y \end{bmatrix}`

**The reflect function does not normalize the vector n.**

Example
-------

.. code-block:: cpp

	#include "include/vec2.h"
	#include <iostream>

	int main() {
		nml::vec2 i(2.0f, -2.0f);
		nml::vec2 n(0.0f, 2.0f); // n is not normalized
		n = nml::normalize(n); // Normalize n
		nml::vec2 c = nml::reflect(i, n);
		std::cout << nml::to_string(c) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[2.000000, 2.000000]