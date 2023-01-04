:orphan:

nml::vec3 nml::reflect(const nml::vec3& i, const nml::vec3& n)
=========================================================================

Return the reflected direction between the incident vector *i* and the normal *n*. *n* should be normalized.

The reflected direction between the incident vector *i* and the normal *n* is calculated this way:

:math:`\begin{bmatrix} i.x \\ i.y \\ i.z \end{bmatrix} - 2.0 * (\begin{bmatrix} n.x \\ n.y \\ n.z \end{bmatrix} \cdot \begin{bmatrix} i.x \\ i.y \\ i.z \end{bmatrix}) * \begin{bmatrix} n.x \\ n.y \\ n.z \end{bmatrix}`

**The reflect function does not normalize the vector n.**

Example
-------

.. code-block:: cpp

	#include "include/vec3.h"
	#include <iostream>

	int main() {
		nml::vec3 i(2.0f, -2.0f, 1.0f);
		nml::vec3 n(0.0f, 4.0f, 0.0f); // n is not normalized
		n = nml::normalize(n); // Normalize n
		nml::vec3 c = nml::reflect(i, n);
		std::cout << nml::to_string(c) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[2.000000, 2.000000, 1.000000]