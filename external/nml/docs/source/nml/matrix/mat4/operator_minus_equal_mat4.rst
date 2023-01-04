:orphan:

mat4: nml::mat4& operator-=(const nml::mat4& other)
===================================================

Substract a *mat4* from the current *mat4*.

The difference between two *mat4* is calculated this way:

:math:`\begin{bmatrix} x.x & y.x & z.x & w.x \\ x.y & y.y & z.y & w.y \\ x.z & y.z & z.z & w.z \\ x.w & y.w & z.w & w.w \end{bmatrix} - \begin{bmatrix} other.x.x & other.y.x & other.z.x & other.w.x \\ other.x.y & other.y.y & other.z.y & other.w.y \\ other.x.z & other.y.z & other.z.z & other.w.z \\ other.x.w & other.y.w & other.z.w & other.w.w \end{bmatrix} =`

:math:`\begin{bmatrix} x.x - other.x.x & y.x - other.y.x & z.x - other.z.x & w.x - other.w.x \\ x.y - other.x.y & y.y - other.y.y & z.y - other.z.y & w.y - other.w.y \\ x.z - other.x.z & y.z - other.y.z & z.z - other.z.z & w.z - other.w.z \\ x.w - other.x.w & y.w - other.y.w & z.w - other.z.w & w.w - other.w.w \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat4.h"
	#include <iostream>

	int main() {
		nml::mat4 a(4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f, 20.0f, 22.0f, 24.0f, 26.0f, 28.0f, 30.0f, 32.0f, 34.0f);
		nml::mat4 b(3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f, 17.0f, 18.0f);
		a -= b;
		std::cout << nml::to_string(a) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[1.000000, 2.000000, 3.000000, 4.000000], [5.000000, 6.000000, 7.000000, 8.000000], [9.000000, 10.000000, 11.000000, 12.000000], [13.000000, 14.000000, 15.000000, 16.000000]]