:orphan:

nml::mat4 inverse(const nml::mat4& mat)
=======================================

Return the inverse of a *mat4*.

The inverse of a *mat4* is calculated this way:

:math:`t = mat^T`

:math:`adj(mat) = \begin{bmatrix} a & e & i & m \\ b & f & j & n \\ c & g & k & o \\ d & h & l & p \end{bmatrix}`

:math:`\small a = det(\begin{bmatrix} t.y.y & t.z.y & t.w.y \\ t.y.z & t.z.z & t.w.z \\ t.y.w & t.z.w & t.w.w)\end{bmatrix} b = -det(\begin{bmatrix} t.y.x & t.z.x & t.w.x \\ t.y.z & t.z.z & t.w.z \\ t.y.w & t.z.w & t.w.w)\end{bmatrix}`

:math:`\small c = det(\begin{bmatrix} t.y.x & t.z.x & t.w.x \\ t.y.y & t.z.y & t.w.y \\ t.y.w & t.z.w & t.w.w)\end{bmatrix} d = -det(\begin{bmatrix} t.y.x & t.z.x & t.w.x \\ t.y.y & t.z.y & t.w.y \\ t.y.z & t.z.z & t.w.z)\end{bmatrix}`

:math:`\small e = -det(\begin{bmatrix} t.x.y & t.z.y & t.w.y \\ t.x.z & t.z.z & t.w.z \\ t.x.w & t.z.w & t.w.w)\end{bmatrix} f = det(\begin{bmatrix} t.x.x & t.z.x & t.w.x \\ t.x.z & t.z.z & t.w.z \\ t.x.w & t.z.w & t.w.w)\end{bmatrix}`

:math:`\small g = -det(\begin{bmatrix} t.x.x & t.z.x & t.w.x \\ t.x.y & t.z.y & t.w.y \\ t.x.w & t.z.w & t.w.w)\end{bmatrix} h = det(\begin{bmatrix} t.x.x & t.z.x & t.w.x \\ t.x.y & t.z.y & t.w.y \\ t.x.z & t.z.z & t.w.z)\end{bmatrix}`

:math:`\small i = det(\begin{bmatrix} t.x.y & t.y.y & t.w.y \\ t.x.z & t.y.z & t.w.z \\ t.x.w & t.y.w & t.w.w)\end{bmatrix} j = -det(\begin{bmatrix} t.x.x & t.y.x & t.w.x \\ t.x.z & t.y.z & t.w.z \\ t.x.w & t.y.w & t.w.w)\end{bmatrix}`

:math:`\small k = det(\begin{bmatrix} t.x.x & t.y.x & t.w.x \\ t.x.y & t.y.y & t.w.y \\ t.x.w & t.y.w & t.w.w)\end{bmatrix} l = -det(\begin{bmatrix} t.x.x & t.y.x & t.w.x \\ t.x.y & t.y.y & t.w.y \\ t.x.z & t.y.z & t.w.z)\end{bmatrix}`

:math:`\small m = -det(\begin{bmatrix} t.x.y & t.y.y & t.z.y \\ t.x.z & t.y.z & t.z.z \\ t.x.w & t.y.w & t.z.w)\end{bmatrix} n = det(\begin{bmatrix} t.x.x & t.y.x & t.z.x \\ t.x.z & t.y.z & t.z.z \\ t.x.w & t.y.w & t.z.w)\end{bmatrix}`

:math:`\small o = -det(\begin{bmatrix} t.x.x & t.y.x & t.z.x \\ t.x.y & t.y.y & t.z.y \\ t.x.w & t.y.w & t.z.w)\end{bmatrix} p = det(\begin{bmatrix} t.x.x & t.y.x & t.z.x \\ t.x.y & t.y.y & t.z.y \\ t.x.z & t.y.z & t.z.z)\end{bmatrix}`

:math:`mat^{-1} = \frac{1.0}{det(mat)} * adj(mat)`

**The inverse function does not check if the matrix is invertible (determinant not null).**

Example
-------

.. code-block:: cpp

	#include "include/mat4.h"
	#include <iostream>

	int main() {
		nml::mat4 a(2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f); // Determinant of a = 16, the matrix is invertible
		nml::mat4 b(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f); // Determinant of b = 0, the matrix is not invertible
		nml::mat4 invA = nml::inverse(a);
		nml::mat4 invB = nml::inverse(b); // Undefined behaviour
		std::cout << nml::to_string(invA) << std::endl;
		std::cout << nml::to_string(invB) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[0.500000, -0.000000, 0.000000, -0.000000], [-0.000000, 0.500000, -0.000000, 0.000000], [0.000000, -0.000000, 0.500000, -0.000000], [-0.000000, 0.000000, -0.000000, 0.500000]]
	[[-nan, -nan, -nan, -nan], [-nan, -nan, -nan, -nan], [-nan, -nan, -nan, -nan], [-nan, -nan, -nan, -nan]]