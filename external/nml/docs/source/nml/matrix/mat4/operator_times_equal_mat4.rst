:orphan:

mat4: nml::mat4& operator*=(const nlm::mat4& other)
===================================================

Multiply to the current *mat4* by a *mat4*.

The product between two *mat4* is calculated this way:

:math:`\begin{bmatrix} x.x & y.x & z.x & w.x \\ x.y & y.y & z.y & w.y \\ x.z & y.z & z.z & w.z \\ x.w & y.w & z.w & w.w \end{bmatrix} * \begin{bmatrix} other.x.x & other.y.x & other.z.x & other.w.x \\ other.x.y & other.y.y & other.z.y & other.w.y \\ other.x.z & other.y.z & other.z.z & other.w.z \\ other.x.w & other.y.w & other.z.w & other.w.w \end{bmatrix} =`

:math:`\begin{bmatrix} a & e & i & m \\ b & f & j & n \\ c & g & k & o \\ d & h & l & p \end{bmatrix}`

:math:`\small a = x.x * other.x.x + y.x * other.x.y + z.x * other.x.z + w.x * other.x.w`
:math:`\small b = x.x * other.y.x + y.x * other.y.y + z.x * other.y.z + w.x * other.y.w`
:math:`\small c = x.x * other.z.x + y.x * other.z.y + z.x * other.z.z + w.x * other.z.w`
:math:`\small d = x.x * other.w.x + y.x * other.w.y + z.x * other.w.z + w.x * other.w.w`
:math:`\small e = x.y * other.x.x + y.y * other.x.y + z.y * other.x.z + w.y * other.x.w`
:math:`\small f = x.y * other.y.x + y.y * other.y.y + z.y * other.y.z + w.y * other.y.w`
:math:`\small g = x.y * other.z.x + y.y * other.z.y + z.y * other.z.z + w.y * other.z.w`
:math:`\small h = x.y * other.w.x + y.y * other.w.y + z.y * other.w.z + w.y * other.w.w`
:math:`\small i = x.z * other.x.x + y.z * other.x.y + z.z * other.x.z + w.z * other.x.w`
:math:`\small j = x.z * other.y.x + y.z * other.y.y + z.z * other.y.z + w.z * other.y.w`
:math:`\small k = x.z * other.z.x + y.z * other.z.y + z.z * other.z.z + w.z * other.z.w`
:math:`\small l = x.z * other.w.x + y.z * other.w.y + z.z * other.w.z + w.z * other.w.w`
:math:`\small m = x.w * other.x.x + y.w * other.x.y + z.w * other.x.z + w.w * other.x.w`
:math:`\small n = x.w * other.y.x + y.w * other.y.y + z.w * other.y.z + w.w * other.y.w`
:math:`\small o = x.w * other.z.x + y.w * other.z.y + z.w * other.z.z + w.w * other.z.w`
:math:`\small p = x.w * other.w.x + y.w * other.w.y + z.w * other.w.z + w.w * other.w.w`

Example
-------

.. code-block:: cpp

	#include "include/mat4.h"
	#include <iostream>

	int main() {
		nml::mat4 a(2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f);
		nml::mat4 b = nml::inverse(a);
		a *= b;
		std::cout << nml::to_string(a) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[1.000000, 0.000000, 0.000000, 0.000000], [0.000000, 1.000000, 0.000000, 0.000000], [0.000000, 0.000000, 1.000000, 0.000000], [0.000000, 0.000000, 0.000000, 1.000000]]