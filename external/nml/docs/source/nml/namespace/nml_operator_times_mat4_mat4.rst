:orphan:

nml::mat4 operator*(nml::mat4 lhs, const nml::mat4& rhs)
========================================================

Return a *mat4* that is the product between two *mat4*.

The product between two *mat4* is calculated this way:

:math:`\begin{bmatrix} lhs.x.x & lhs.y.x & lhs.z.x & lhs.w.x \\ lhs.x.y & lhs.y.y & lhs.z.y & lhs.w.y \\ lhs.x.z & lhs.y.z & lhs.z.z & lhs.w.z \\ lhs.x.w & lhs.y.w & lhs.z.w & lhs.w.w \end{bmatrix} * \begin{bmatrix} rhs.x.x & rhs.y.x & rhs.z.x & rhs.w.x \\ rhs.x.y & rhs.y.y & rhs.z.y & rhs.w.y \\ rhs.x.z & rhs.y.z & rhs.z.z & rhs.w.z \\ rhs.x.w & rhs.y.w & rhs.z.w & rhs.w.w \end{bmatrix} =`

:math:`\begin{bmatrix} a & e & i & m \\ b & f & j & n \\ c & g & k & o \\ d & h & l & p \end{bmatrix}`

:math:`\small a = lhs.x.x * rhs.x.x + lhs.y.x * rhs.x.y + lhs.z.x * rhs.x.z + lhs.w.x * rhs.x.w`
:math:`\small b = lhs.x.x * rhs.y.x + lhs.y.x * rhs.y.y + lhs.z.x * rhs.y.z + lhs.w.x * rhs.y.w`
:math:`\small c = lhs.x.x * rhs.z.x + lhs.y.x * rhs.z.y + lhs.z.x * rhs.z.z + lhs.w.x * rhs.z.w`
:math:`\small d = lhs.x.x * rhs.w.x + lhs.y.x * rhs.w.y + lhs.z.x * rhs.w.z + lhs.w.x * rhs.w.w`
:math:`\small e = lhs.x.y * rhs.x.x + lhs.y.y * rhs.x.y + lhs.z.y * rhs.x.z + lhs.w.y * rhs.x.w`
:math:`\small f = lhs.x.y * rhs.y.x + lhs.y.y * rhs.y.y + lhs.z.y * rhs.y.z + lhs.w.y * rhs.y.w`
:math:`\small g = lhs.x.y * rhs.z.x + lhs.y.y * rhs.z.y + lhs.z.y * rhs.z.z + lhs.w.y * rhs.z.w`
:math:`\small h = lhs.x.y * rhs.w.x + lhs.y.y * rhs.w.y + lhs.z.y * rhs.w.z + lhs.w.y * rhs.w.w`
:math:`\small i = lhs.x.z * rhs.x.x + lhs.y.z * rhs.x.y + lhs.z.z * rhs.x.z + lhs.w.z * rhs.x.w`
:math:`\small j = lhs.x.z * rhs.y.x + lhs.y.z * rhs.y.y + lhs.z.z * rhs.y.z + lhs.w.z * rhs.y.w`
:math:`\small k = lhs.x.z * rhs.z.x + lhs.y.z * rhs.z.y + lhs.z.z * rhs.z.z + lhs.w.z * rhs.z.w`
:math:`\small l = lhs.x.z * rhs.w.x + lhs.y.z * rhs.w.y + lhs.z.z * rhs.w.z + lhs.w.z * rhs.w.w`
:math:`\small m = lhs.x.w * rhs.x.x + lhs.y.w * rhs.x.y + lhs.z.w * rhs.x.z + lhs.w.w * rhs.x.w`
:math:`\small n = lhs.x.w * rhs.y.x + lhs.y.w * rhs.y.y + lhs.z.w * rhs.y.z + lhs.w.w * rhs.y.w`
:math:`\small o = lhs.x.w * rhs.z.x + lhs.y.w * rhs.z.y + lhs.z.w * rhs.z.z + lhs.w.w * rhs.z.w`
:math:`\small p = lhs.x.w * rhs.w.x + lhs.y.w * rhs.w.y + lhs.z.w * rhs.w.z + lhs.w.w * rhs.w.w`

Example
-------

.. code-block:: cpp

	#include "include/mat4.h"
	#include <iostream>

	int main() {
		nml::mat4 a(2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f);
		nml::mat4 b = nml::inverse(a);
		nml::mat4 c = a * b;
		std::cout << nml::to_string(c) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[1.000000, 0.000000, 0.000000, 0.000000], [0.000000, 1.000000, 0.000000, 0.000000], [0.000000, 0.000000, 1.000000, 0.000000], [0.000000, 0.000000, 0.000000, 1.000000]]