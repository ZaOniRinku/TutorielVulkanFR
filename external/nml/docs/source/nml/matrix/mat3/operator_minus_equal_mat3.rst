:orphan:

mat3: nml::mat3& operator-=(const nml::mat3& other)
===================================================

Substract a *mat3* from the current *mat3*.

The difference between two *mat3* is calculated this way:

:math:`\begin{bmatrix} x.x & y.x & z.x \\ x.y & y.y & z.y \\ x.z & y.z & z.z \end{bmatrix} - \begin{bmatrix} other.x.x & other.y.x & other.z.x \\ other.x.y & other.y.y & other.z.y \\ other.x.z & other.y.z & other.z.z \end{bmatrix} =`

:math:`\begin{bmatrix} x.x - other.x.x & y.x - other.y.x & z.x - other.z.x \\ x.y - other.x.y & y.y - other.y.y & z.y - other.z.y \\ x.z - other.x.z & y.z - other.y.z & z.z - other.z.z \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat3.h"
	#include <iostream>

	int main() {
		nml::mat3 a(4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f, 20.0f);
		nml::mat3 b(3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f);
		a -= b;
		std::cout << nml::to_string(a) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[1.000000, 2.000000, 3.000000], [4.000000, 5.000000, 6.000000], [7.000000, 8.000000, 9.000000]]