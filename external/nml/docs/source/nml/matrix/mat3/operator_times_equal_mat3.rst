:orphan:

mat3: nml::mat3& operator*=(const nlm::mat3& other)
===================================================

Multiply the current *mat3* by a *mat3*.

The product between two *mat3* is calculated this way:

:math:`\begin{bmatrix} x.x & y.x & z.x \\ x.y & y.y & z.y \\ x.z & y.z & z.z \end{bmatrix} * \begin{bmatrix} other.x.x & other.y.x & other.z.x \\ other.x.y & other.y.y & other.z.y \\ other.x.z & other.y.z & other.z.z \end{bmatrix} =`

:math:`\tiny \begin{bmatrix} x.x * other.x.x + y.x * other.x.y + z.x * other.x.z & x.x * other.y.x + y.x * other.y.y + z.x * other.y.z & x.x * other.z.x + y.x * other.z.y + z.x * other.z.z \\ x.y * other.x.x + y.y * other.x.y + z.y * other.x.z & x.y * other.y.x + y.y * other.y.y + z.y * other.y.z & x.y * other.z.x + y.y * other.z.y + z.y * other.z.z \\ x.z * other.x.x + y.z * other.x.y + z.z * other.x.z & x.z * other.y.x + y.z * other.y.y + z.z * other.y.z & x.z * other.z.x + y.z * other.z.y + z.z * other.z.z \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat3.h"
	#include <iostream>

	int main() {
		nml::mat3 a(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 10.0f);
		nml::mat3 b = nml::inverse(a);
		a *= b;
		std::cout << nml::to_string(a) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[1.000000, 0.000000, 0.000000], [0.000000, 1.000000, 0.000000], [0.000000, 0.000000, 1.000000]]