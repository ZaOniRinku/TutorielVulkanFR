:orphan:

nml::vec2 nml::refract(const nml::vec2& i, const nml::vec2& n, float ior)
=========================================================================

Return the refracted direction between the incident vector *i*, the normal *n* and the ratio of indices of refraction *ior*. *n* should be normalized.

The refracted direction between the incident vector *i*, the normal *n* and the ratio of indices of refraction *ior* is calculated this way:

:math:`k = 1.0 - ior^2 * (1.0 - (\begin{bmatrix} n.x \\ n.y \end{bmatrix} \cdot \begin{bmatrix} i.x \\ i.y \end{bmatrix})^2)`

:math:`\begin{cases} \begin{bmatrix} 0.0 \\ 0.0 \end{bmatrix}, & \text{if } k < 0.0 \\ ior * \begin{bmatrix} i.x \\ i.y \end{bmatrix} - (ior * (\begin{bmatrix} n.x \\ n.y \end{bmatrix} \cdot \begin{bmatrix} i.x \\ i.y \end{bmatrix}) + \sqrt{k}) * \begin{bmatrix} n.x \\ n.y \end{bmatrix}, & \text{otherwise} \end{cases}`

**The refract function does not normalize the vector n.**

Example
-------

.. code-block:: cpp

	#include "include/vec2.h"
	#include <iostream>

	int main() {
		nml::vec2 i(2.0f, -2.0f);
		nml::vec2 n(0.0f, 2.0f); // n is not normalized
		n = nml::normalize(n); // Normalize n
		nml::vec2 c = nml::refract(i, n, 0.5f);
		std::cout << nml::to_string(c) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[1.000000, -1.322876]