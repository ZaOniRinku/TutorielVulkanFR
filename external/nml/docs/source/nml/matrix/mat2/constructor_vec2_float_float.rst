:orphan:

mat2: mat2(nlm::vec2 _xxxy, float _yx, float _yy)
=================================================

Construct a ([*_xxxy.x*, *_xxxy.y*], [*_yx*, *_yy*]) matrix.

:math:`\begin{bmatrix} \_xxxy.x & \_yx \\ \_xxxy.y & \_yy \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat2.h"
	#include <iostream>

	int main() {
		nml::mat2 m(nml::vec2(1.0f, 2.0f), 3.0f, 4.0f);
		std::cout << nml::to_string(m) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[1.000000, 2.000000], [3.000000, 4.000000]]