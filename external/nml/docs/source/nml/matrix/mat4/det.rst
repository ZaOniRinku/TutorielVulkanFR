:orphan:

mat4: float det() const
=======================

Return the determinant of the matrix.

The determinant of a *mat4* is calculated this way:
	
:math:`\scriptsize det = x.x * (y.y * z.z * w.w - y.y * w.z * z.w - z.y * y.z * w.w + z.y * w.z * y.w + w.y * y.z * z.w - w.y * z.z * y.w) -`
:math:`\scriptsize y.x * (x.y * z.z * w.w - x.y * w.z * z.w - z.y * x.z * w.w + z.y * w.z * x.w + w.y * x.z * z.w - w.y * z.z * x.w) +`
:math:`\scriptsize z.x * (x.y * y.z * w.w - x.y * w.z * y.w - y.y * x.z * w.w + y.y * w.z * x.w + w.y * x.z * y.w - w.y * y.z * x.w) -`
:math:`\scriptsize w.x * (x.y * y.z * z.w - x.y * z.z * y.w - y.y * x.z * z.w + y.y * z.z * x.w + z.y * x.z * y.w - z.y * y.z * x.w)`

Example
-------

.. code-block:: cpp

	#include "include/mat4.h"
	#include <iostream>

	int main() {
		nml::mat4 m(1.0f, 2.0f, 4.0f, 8.0f, 16.0f, 32.0f, 64.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
		std::cout << m.det() << std::endl;

		return 0;
	}

Result:

.. code-block::

	480