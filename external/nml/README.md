# nml - Nutshell Mathematics Library
C++ Mathematics library for Computer Graphics.

## Documentation
Documentation for nml is available [here](https://team-nutshell.github.io/nml/).

## Get nml
```
git clone https://github.com/Team-Nutshell/nml.git
```

## Add nml to a CMake project
This example has nml inside an ``external`` directory:
```CMake
add_subdirectory(external/nml)
target_include_directories(${PROJECT_NAME} PUBLIC external/nml)
target_link_libraries(${PROJECT_NAME} PUBLIC nml)
```

## Use nml
Examples with ``vec2``:
```CPP
#include "external/nml/include/vec2.h"
#include "external/nml/include/vec3.h"
#include "external/nml/include/vec4.h"

int main() {
    nml::vec2 i(1.0f, -1.0f); // Create a 2D vector with values x = 1.0 and y = 2.0
    i = nml::normalize(i); // Get a normalized vector
    nml::vec2 n(0.0f, -1.0f);
    nml::vec2 r = nml::reflect(i, n); // Calculate the reflection direction from the incident vector i and the normal n
}
```