# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project(afk)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 23)

file(GLOB LIBCOMBAT_HEADERS "libcombat/libcombat/*.hpp")
file(GLOB LIBCOMBAT_SOURCES "libcombat/libcombat/details/*.cpp")

file(GLOB TEST_HEADERS "libcombat/tests/*.hpp")
file(GLOB TEST_SOURCES "libcombat/tests/*.cpp")

add_executable(tests ${TEST_HEADERS} ${TEST_SOURCES})

# Add the source files for the library
add_library(libcombat SHARED ${LIBCOMBAT_HEADERS} ${LIBCOMBAT_SOURCES})

# Set any additional compiler flags or options
# For example:
target_compile_options(libcombat PRIVATE -Wall)
target_compile_options(tests PRIVATE -Wall)

# Set the installation directory for the library
# For example:
# install(TARGETS libcombat DESTINATION lib)

# Set the include directory for the library
# For example:
target_include_directories(libcombat PRIVATE libcombat/)
target_include_directories(tests PRIVATE libcombat/)

# target_compile_definitions(libcombat PRIVATE LIBCOMBAT_BUILD)


target_link_libraries(tests PRIVATE libcombat)
