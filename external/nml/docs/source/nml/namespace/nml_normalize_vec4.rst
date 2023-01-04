:orphan:

nml::vec4 nml::normalize(const nml::vec4& vec)
==============================================

Return a *vec4* with the same direction as *vec* but with length 1.

The normalization of a *vec4* is calculated this way:
	
:math:`norm(\begin{bmatrix} vec.x \\ vec.y \\ vec.z \\ vec.w \end{bmatrix}) = \begin{bmatrix} \frac{vec.x}{\left \| vec \right \|} \\ \frac{vec.y}{\left \| vec \right \|} \\ \frac{vec.z}{\left \| vec \right \|} \\ \frac{vec.w}{\left \| vec \right \|} \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/vec4.h"
	#include <iostream>

	int main() {
		nml::vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
		std::cout << a.length() << std::endl;
		nml::vec4 b = nml::normalize(a);
		std::cout << nml::to_string(b) << std::endl;
		std::cout << b.length() << std::endl;

		return 0;
	}

Result:

.. code-block::

	5.47723
	[0.182574, 0.365148, 0.547723, 0.730297]
	1