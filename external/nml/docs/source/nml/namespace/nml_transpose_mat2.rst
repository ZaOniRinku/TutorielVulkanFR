:orphan:

nml::mat2 transpose(const nml::mat2& mat)
=========================================

Return a *mat2* where the columns of *mat* are the rows and the rows of *mat* are the columns.

The transpose of a *mat2* is calculated this way:

:math:`\begin{bmatrix} x.x & y.x \\ x.y & y.y \end{bmatrix}^T = \begin{bmatrix} x.x & x.y \\ y.x & y.y \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat2.h"
	#include <iostream>

	int main() {
		nml::mat2 a(1.0f, 2.0f, 3.0f, 4.0f);
		std::cout << nml::to_string(a) << std::endl;
		nml::mat2 b = nml::transpose(a);
		std::cout << nml::to_string(b) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[1.000000, 2.000000], [3.000000, 4.000000]]
	[[1.000000, 3.000000], [2.000000, 4.000000]]