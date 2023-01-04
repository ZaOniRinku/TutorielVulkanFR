:orphan:

nml::mat4 orthoRH(const float left, const float right, const float bottom, const float top, const float near, const float far)
==============================================================================================================================

Return a right-hand orthographic projection matrix.

The right-hand orthographic projection matrix is calculated this way:

:math:`\begin{bmatrix} \frac{2.0}{right - left} & 0.0 & 0.0 & -\frac{right + left}{right - left} \\ 0.0 & \frac{2.0}{top - bottom} & 0.0 & -\frac{top + bottom}{top - bottom} \\ 0.0 & 0.0 & \frac{-1.0}{far - near} & -\frac{near}{far - near} \\ 0.0 & 0.0 & 0.0 & 1.0 \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "../nml/include/mat4.h"
	#include <iostream>

	int main() {
		nml::mat4 m = nml::orthoRH(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 10.0f);
		std::cout << nml::to_string(m) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[0.100000, 0.000000, 0.000000, 0.000000], [0.000000, 0.100000, 0.000000, 0.000000], [0.000000, 0.000000, -0.050000, 0.000000], [-0.000000, -0.000000, 0.500000, 1.000000]]