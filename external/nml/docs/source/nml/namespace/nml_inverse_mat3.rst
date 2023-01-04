:orphan:

nml::mat3 inverse(const nml::mat3& mat)
=======================================

Return the inverse of a *mat3*.

The inverse of a *mat3* is calculated this way:

:math:`t = mat^T`

:math:`adj(mat) = \begin{bmatrix} a & d & g \\ b & e & h \\ c & f & i \end{bmatrix}`

:math:`a = det(\begin{bmatrix} t.y.y & t.z.y \\ t.y.z & t.z.z \end{bmatrix})`

:math:`b = -det(\begin{bmatrix} t.y.x & t.z.x \\ t.y.z & t.z.z \end{bmatrix})`

:math:`c = det(\begin{bmatrix} t.y.x & t.z.x \\ t.y.y & t.z.y \end{bmatrix})`

:math:`d = -det(\begin{bmatrix} t.x.y & t.z.y \\ t.x.z & t.z.z \end{bmatrix})`

:math:`e = det(\begin{bmatrix} t.x.x & t.z.x \\ t.x.z & t.z.z \end{bmatrix})`

:math:`f = -det(\begin{bmatrix} t.x.x & t.z.x \\ t.x.y & t.z.y \end{bmatrix})`

:math:`g = det(\begin{bmatrix} t.x.y & t.y.y \\ t.x.z & t.y.z \end{bmatrix})`

:math:`h = -det(\begin{bmatrix} t.x.x & t.y.x \\ t.x.z & t.y.z \end{bmatrix})`

:math:`i = -det(\begin{bmatrix} t.x.x & t.y.x \\ t.x.y & t.y.y \end{bmatrix})`

:math:`mat^{-1} = \frac{1.0}{det(mat)} * adj(mat)`

**The inverse function does not check if the matrix is invertible (determinant not null).**

Example
-------

.. code-block:: cpp

	#include "include/mat3.h"
	#include <iostream>

	int main() {
		nml::mat3 a(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 10.0f); // Determinant of a = -3, the matrix is invertible
		nml::mat3 b(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f); // Determinant of b = 0, the matrix is not invertible
		nml::mat3 invA = nml::inverse(a);
		nml::mat3 invB = nml::inverse(b); // Undefined behaviour
		std::cout << nml::to_string(invA) << std::endl;
		std::cout << nml::to_string(invB) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[-0.666667, -1.333333, 1.000000], [-0.666667, 3.666667, -2.000000], [1.000000, -2.000000, 1.000000]]
	[[-inf, inf, -inf], [inf, -inf, inf], [-inf, inf, -inf]]