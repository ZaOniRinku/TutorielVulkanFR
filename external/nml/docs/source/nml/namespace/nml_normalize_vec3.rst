:orphan:

nml::vec3 nml::normalize(const nml::vec3& vec)
==============================================

Return a *vec3* with the same direction as *vec* but with length 1.

The normalization of a *vec3* is calculated this way:
	
:math:`norm(\begin{bmatrix} vec.x \\ vec.y \\ vec.z \end{bmatrix}) = \begin{bmatrix} \frac{vec.x}{\left \| vec \right \|} \\ \frac{vec.y}{\left \| vec \right \|} \\ \frac{vec.z}{\left \| vec \right \|} \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec3.h"
	#include <iostream>

	int main() {
		nml::vec3 a(1.0f, 2.0f, 3.0f);
		std::cout << a.length() << std::endl;
		nml::vec3 b = nml::normalize(a);
		std::cout << nml::to_string(b) << std::endl;
		std::cout << b.length() << std::endl;

		return 0;
	}

Result:

.. code-block::

	3.74166
	[0.267261, 0.534522, 0.801784]
	1