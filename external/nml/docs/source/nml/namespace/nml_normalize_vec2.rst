:orphan:

nml::vec2 nml::normalize(const nml::vec2& vec)
==============================================

Return a *vec2* with the same direction as *vec* but with length 1.

The normalization of a *vec2* is calculated this way:
	
:math:`norm(\begin{bmatrix} vec.x \\ vec.y \end{bmatrix}) = \begin{bmatrix} \frac{vec.x}{\left \| vec \right \|} \\ \frac{vec.y}{\left \| vec \right \|} \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec2.h"
	#include <iostream>

	int main() {
		nml::vec2 a(1.0f, 2.0f);
		std::cout << a.length() << std::endl;
		nml::vec2 b = nml::normalize(a);
		std::cout << nml::to_string(b) << std::endl;
		std::cout << b.length() << std::endl;

		return 0;
	}

Result:

.. code-block::

	2.23607
	[0.447214, 0.894427]
	1