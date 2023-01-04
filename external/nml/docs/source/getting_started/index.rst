Getting started
===============

Get nml
-------

nml is available on `GitHub <https://github.com/Team-Nutshell/nml>`_.

.. code-block:: shell

	git clone https://github.com/Team-Nutshell/nml.git

Add nml to a CMake project
--------------------------

nml can be built as a static library with the library name ``nml``.

Replace *<path_to_nml>* by the path to the nml source code directory.

.. code-block:: cmake

	add_subdirectory(<path_to_nml>/nml)

	target_include_directories(${PROJECT_NAME} PUBLIC <path_to_nml>/nml)
	target_link_libraries(${PROJECT_NAME} PUBLIC nml)

Use nml
-------

In these samples, replace *<path_to_nml>* by the path to the nml source code directory.

It is possible to include the entire nml library with one ``include``:

.. code-block:: cpp

	#include "<path_to_nml>/include/nml.h"

Or only include the needed headers:

.. code-block:: cpp

	#include "<path_to_nml>/include/vec2.h"
	#include "<path_to_nml>/include/vec3.h"
	#include "<path_to_nml>/include/mat4.h"