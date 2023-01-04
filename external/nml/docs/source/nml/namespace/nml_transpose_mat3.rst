:orphan:

nml::mat3 transpose(const nml::mat3& mat)
=========================================

Return a *mat3* where the columns of *mat* are the rows and the rows of *mat* are the columns.

The transpose of a *mat3* is calculated this way:

:math:`\begin{bmatrix} x.x & y.x & z.x \\ x.y & y.y & z.y \\ x.z & y.z & z.z \end{bmatrix}^T = \begin{bmatrix} x.x & x.y & x.z \\ y.x & y.y & y.z \\ z.x & z.y & z.z \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat3.h"
	#include <iostream>

	int main() {
		nml::mat3 a(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
		std::cout << nml::to_string(a) << std::endl;
		nml::mat3 b = nml::transpose(a);
		std::cout << nml::to_string(b) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[1.000000, 2.000000, 3.000000], [4.000000, 5.000000, 6.000000], [7.000000, 8.000000, 9.000000]]
	[[1.000000, 4.000000, 7.000000], [2.000000, 5.000000, 8.000000], [3.000000, 6.000000, 9.000000]]