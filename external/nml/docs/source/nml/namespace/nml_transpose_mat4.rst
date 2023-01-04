:orphan:

nml::mat4 transpose(const nml::mat4& mat)
=========================================

Return a *mat4* where the columns of *mat* are the rows and the rows of *mat* are the columns.

The transpose of a *mat4* is calculated this way:

:math:`\begin{bmatrix} x.x & y.x & z.x & w.x \\ x.y & y.y & z.y & w.y \\ x.z & y.z & z.z & w.z \\ x.w & y.w & z.w & w.w \end{bmatrix}^T = \begin{bmatrix} x.x & x.y & x.z & x.w \\ y.x & y.y & y.z & y.w \\ z.x & z.y & z.z & z.w \\ w.x & w.y & w.z & w.w \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat4.h"
	#include <iostream>

	int main() {
		nml::mat4 a(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
		std::cout << nml::to_string(a) << std::endl;
		nml::mat4 b = nml::transpose(a);
		std::cout << nml::to_string(b) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[1.000000, 2.000000, 3.000000, 4.000000], [5.000000, 6.000000, 7.000000, 8.000000], [9.000000, 10.000000, 11.000000, 12.000000], [13.000000, 14.000000, 15.000000, 16.000000]]
	[[1.000000, 5.000000, 9.000000, 13.000000], [2.000000, 6.000000, 10.000000, 14.000000], [3.000000, 7.000000, 11.000000, 15.000000], [4.000000, 8.000000, 12.000000, 16.000000]]