cmake_minimum_required(VERSION 3.7 FATAL_ERROR) # Demande au moins la version 3.7 de CMake, puisque find_package(Vulkan) n'est disponible qu'à partir de la version 3.7 de CMake
set(NAME TutorielVulkanFR) # Crée une variable CMake s'appelant NAME contenant TutorielVulkanFR, le nom du projet
project(${NAME} VERSION 0.0.1 LANGUAGES C CXX) # Définit un nouveau projet utilisant le nom défini à la ligne précédente, en version 0.0.1 (ce n'est pas important) et qui utilisera du C et du C++

set(CMAKE_CXX_STANDARD 17) # Définit le standard de C++ utilisé comme étant C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Force l'utilisation de C++17

set(TUTORIEL_VK_DEFINES "") # Définit une nouvelle variable appelée TUTORIEL_VK_DEFINES qui est vide pour le moment, elle servira à passer des constantes lors de la construction du projet

if(CMAKE_SYSTEM_NAME STREQUAL "Windows") # Si nous sommes sur Windows
	list(APPEND TUTORIEL_VK_DEFINES TUTORIEL_VK_OS_WINDOWS _CRT_SECURE_NO_WARNINGS NOMINMAX) # On ajoute à TUTORIEL_VK_DEFINES les constantes TUTORIEL_VK_OS_WINDOWS qu'on utilisera lorsqu'on souhaitera écrire du code spécifique à Windows ainsi que _CRT_SECURE_NO_WARNINGS qui retire les warnings liés à l'utilisation de certaines fonctions considérées unsafe par le compilateur MSVC (scanf, par exemple, même si nous n'allons pas les utiliser ici), ainsi que NOMINMAX qui permet de ne pas définir les fonctions min() et max() lorsque nous allons inclure windows.h
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux") # Si nous sommes sur Linux
	list(APPEND TUTORIEL_VK_DEFINES TUTORIEL_VK_OS_LINUX) # On ajoute à TUTORIEL_VK_DEFINES la constante TUTORIEL_VK_OS_LINUX qu'on utilisera lorsqu'on souhaitera écrire du code spécifique à Linux
endif()

add_subdirectory(external/glfw) # On appelle le fichier CMake de GLFW
add_subdirectory(external/glslang) # On appelle le fichier CMake de Glslang
add_subdirectory(external/nml) # On appelle le fichier CMake de nml
add_subdirectory(external/VulkanMemoryAllocator) # On appelle le fichier CMake de VulkanMemoryAllocator

find_package(Vulkan) # On demande à CMake de chercher Vulkan
if(NOT Vulkan_FOUND) # Si CMake n'a pas réussi à trouver Vulkan
	message(FATAL_ERROR "Impossible de trouver Vulkan.") # Arrête CMake et affiche un message d'erreur
else() # Si CMake a réussi à trouver Vulkan
	message(STATUS "Vulkan a été trouvé.") # Affiche un message de succès
endif()

set(SOURCES
	src/renderingengine.cpp)
set(HEADERS
	src/renderingengine.h)

add_executable(${PROJECT_NAME} src/main.cpp ${SOURCES} ${HEADERS}) # On va vouloir créer un exécutable du même nom que le projet et avec les fichiers du dossier src

target_link_libraries(${PROJECT_NAME} PRIVATE glfw glslang SPIRV nml VulkanMemoryAllocator Vulkan::Vulkan) # On lie GLFW, glslang, SPIRV (inclut dans Glslang), nml, VulkanMemoryAllocator et Vulkan à notre projet

target_compile_definitions(${PROJECT_NAME} PRIVATE
	${TUTORIEL_VK_DEFINES}) # On ajoute toutes les définitions qu'on a créées plus haut