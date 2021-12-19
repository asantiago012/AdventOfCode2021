# CMakeList.txt: proyecto de CMake para AdventOfCode2021, incluya el origen y defina
# la lógica específica del proyecto aquí.
#
cmake_minimum_required (VERSION 3.8)


# Agregue un origen al ejecutable de este proyecto.
add_library(LibUtils STATIC Utils.cpp Utils.h)
add_executable (AdventOfCode2021 AdventOfCode2021.cpp AdventOfCode2021.h)

target_link_libraries(AdventOfCode2021 PUBLIC LibUtils)

# TODO: Agregue pruebas y destinos de instalación si es necesario.

# add compilation flags
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -g)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:${PROJECT_NAME}>/data)