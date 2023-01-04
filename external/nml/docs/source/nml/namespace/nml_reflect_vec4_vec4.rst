:orphan:

nml::vec4 nml::reflect(const nml::vec4& i, const nml::vec4& n)
=========================================================================

Return the reflected direction between the incident vector *i* and the normal *n*. *n* should be normalized.

The reflected direction between the incident vector *i* and the normal *n* is calculated this way:

:math:`\begin{bmatrix} i.x \\ i.y \\ i.z \\ i.w \end{bmatrix} - 2.0 * (\begin{bmatrix} n.x \\ n.y \\ n.z \\ n.w \end{bmatrix} \cdot \begin{bmatrix} i.x \\ i.y \\ i.z \\ i.w \end{bmatrix}) * \begin{bmatrix} n.x \\ n.y \\ n.z \\ n.w \end{bmatrix}`

**The reflect function does not normalize the vector n.**

Example
-------

.. code-block:: cpp

	#include "include/vec4.h"
	#include <iostream>

	int main() {
		nml::vec4 i(2.0f, -2.0f, 1.0f, 0.0f);
		nml::vec4 n(0.0f, 4.0f, 0.0f, 0.0f); // n is not normalized
		n = nml::normalize(n); // Normalize n
		nml::vec4 c = nml::reflect(i, n);
		std::cout << nml::to_string(c) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[2.000000, 2.000000, 1.000000, 0.000000]