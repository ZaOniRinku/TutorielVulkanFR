:orphan:

mat2: mat2(nlm::vec2 _xxxy, nlm::vec2 _yxyy)
============================================

Construct a ([*_xxxy.x*, *_xxxy.y*], [*_yxyy.x*, *_yxyy.y*]) matrix.

:math:`\begin{bmatrix} \_xxxy.x & \_yxyy.x \\ \_xxxy.y & \_yxyy.y \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat2.h"
	#include <iostream>

	int main() {
		nml::mat2 m(nml::vec2(1.0f, 2.0f), nml::vec2(3.0f, 4.0f));
		std::cout << nml::to_string(m) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[1.000000, 2.000000], [3.000000, 4.000000]]