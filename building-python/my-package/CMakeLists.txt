cmake_minimum_required(VERSION 3.5.0)
project(extension LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 11)

find_package(PythonExtensions REQUIRED)

add_library(math MODULE my_package/math/math11.cpp)
python_extension_module(math)

if (MSVC)
endif ()

install(TARGETS math LIBRARY DESTINATION my_package)
