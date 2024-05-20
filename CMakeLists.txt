cmake_minimum_required(VERSION 3.5)
project(MINI_OpenVR_Driver CXX)

set(OPENVR_LIB_DIR ${CMAKE_SOURCE_DIR}/external/openvr/lib/win64 CACHE STRING "OpenVR .lib directory")
set(OPENVR_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/openvr/headers CACHE STRING "OpenVR include directory")
set(OPENVR_IMPLEMENTATION_DIR ${CMAKE_SOURCE_DIR}/external/openvr/bin/win64 CACHE STRING "OpenVR implementation (dll, so, dylib)")
set(EIGEN_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/eigen CACHE STRING "Eigen include directory")

add_subdirectory(northstar)