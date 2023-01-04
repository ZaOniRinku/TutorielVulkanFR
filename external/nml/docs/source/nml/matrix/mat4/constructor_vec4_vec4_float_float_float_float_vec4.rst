:orphan:

mat4: mat4(nml::vec4 _xxxyxzxw, nml::vec4 _yxyyyzyw, float _zx, float _zy, float _zz, float _zw, nml::vec4 _wxwywzww)
=====================================================================================================================

Construct a ([*_xxxyxzxw.x*, *_xxxyxzxw.y*, *_xxxyxzxw.z*, *_xxxyxzxw.w*], [*_yxyyyzyw.x*, *_yxyyyzyw.y*, *_yxyyyzyw.z*, *_yxyyyzyw.w*], [*_zx*, *_zy*, *_zz*, *_zw*], [*_wxwywzww.x*, *_wxwywzww.y*, *_wxwywzww.z*, *_wxwywzww.w*]) matrix.

:math:`\begin{bmatrix} \_xxxyxzxw.x & \_yxyyyzyw.x & \_zx & \_wxwywzww.x \\ \_xxxyxzxw.y & \_yxyyyzyw.y & \_zy & \_wxwywzww.y \\ \_xxxyxzxw.z & \_yxyyyzyw.z & \_zz & \_wxwywzww.z \\ \_xxxyxzxw.w & \_yxyyyzyw.w & \_zw & \_wxwywzww.w \end{bmatrix}`

Example
-------

.. code-block:: cpp

	#include "include/mat4.h"
	#include <iostream>

	int main() {
		nml::mat4 m(nml::vec4(1.0f, 2.0f, 3.0f, 4.0f), nml::vec4(5.0f, 6.0f, 7.0f, 8.0f), 9.0f, 10.0f, 11.0f, 12.0f, nml::vec4(13.0f, 14.0f, 15.0f, 16.0f));
		std::cout << nml::to_string(m) << std::endl;

		return 0;
	}

Result:

.. code-block::

	[[1.000000, 2.000000, 3.000000, 4.000000], [5.000000, 6.000000, 7.000000, 8.000000], [9.000000, 10.000000, 11.000000, 12.000000], [13.000000, 14.000000, 15.000000, 16.000000]]