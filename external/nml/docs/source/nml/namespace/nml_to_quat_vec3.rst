:orphan:

nml::quat nml::to_quat(const nml::vec3& vec)
============================================

Return a quaternion from euler angles.

The conversion from euler angles to quaternion is calculated this way:

:math:`(\cos(\frac{vec.x}{2.0}) * \cos(\frac{vec.y}{2.0}) * \cos(\frac{vec.z}{2.0}) + \sin(\frac{vec.x}{2.0}) * \sin(\frac{vec.y}{2.0}) * \sin(\frac{vec.z}{2.0})) +`
:math:`(\sin(\frac{vec.x}{2.0}) * \cos(\frac{vec.y}{2.0}) * \cos(\frac{vec.z}{2.0}) - \cos(\frac{vec.x}{2.0}) * \sin(\frac{vec.y}{2.0}) * \sin(\frac{vec.z}{2.0}))i +`
:math:`(\cos(\frac{vec.x}{2.0}) * \sin(\frac{vec.y}{2.0}) * \cos(\frac{vec.z}{2.0}) + \sin(\frac{vec.x}{2.0}) * \cos(\frac{vec.y}{2.0}) * \sin(\frac{vec.z}{2.0}))j +`
:math:`(\cos(\frac{vec.x}{2.0}) * \cos(\frac{vec.y}{2.0}) * \sin(\frac{vec.z}{2.0}) - \sin(\frac{vec.x}{2.0}) * \sin(\frac{vec.y}{2.0}) * \cos(\frac{vec.z}{2.0}))k +`

Example
-------

.. code-block:: cpp

	#include "include/quat.h"
	#include "include/vec3.h"
	#include <iostream>

	int main() {
		nml::vec3 v(1.570796f, 0.000000f, 1.570796f);
		nml::quat q = nml::to_quat(v);
		std::cout << nml::to_string(q) << std::endl;

		return 0;
	}

Result:

.. code-block::

	0.500000 + 0.500000i + 0.500000j + 0.500000k