# CMakeList.txt: proyecto de CMake para AdventOfCode2021_cmake, incluya el origen y defina
# la lógica específica del proyecto aquí.
#
cmake_minimum_required (VERSION 3.8)


# Agregue un origen al ejecutable de este proyecto.
add_library(LibUtils STATIC Utils.cpp Utils.h)
add_executable (AdventOfCode2021_cmake AdventOfCode2021_cmake.cpp AdventOfCode2021_cmake.h)

target_link_libraries(AdventOfCode2021_cmake PUBLIC LibUtils)

# TODO: Agregue pruebas y destinos de instalación si es necesario.
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/inputs $<TARGET_FILE_DIR:${PROJECT_NAME}>/inputs)