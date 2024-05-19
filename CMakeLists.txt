cmake_minimum_required(VERSION 3.5)
project(Northstar_OpenVR CXX)

set(OPENVR_LIB_DIR ${CMAKE_SOURCE_DIR}/external/openvr/lib/win64 CACHE STRING "OpenVR .lib directory")
set(OPENVR_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/openvr/headers CACHE STRING "OpenVR include directory")
set(OPENVR_IMPLEMENTATION_DIR ${CMAKE_SOURCE_DIR}/external/openvr/bin/win64 CACHE STRING "OpenVR implementation (dll, so, dylib)")
set(STRUCTURE_LIB_DIR ${CMAKE_SOURCE_DIR}/external/structure/lib CACHE STRING "Perception Engine .lib directory")
set(STRUCTURE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/structure/include CACHE STRING "Perception Engine include directory")
set(STRUCTURE_IMPLEMENTATION_DIR ${CMAKE_SOURCE_DIR}/external/structure/bin CACHE STRING "Perception Engine implementation (dll, so, dylib)")
set(GLEW_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/glew/include CACHE STRING "Glew include directory")
set(EIGEN_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/eigen CACHE STRING "Eigen include directory")
set(DOCTEST_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/doctest CACHE STRING "Doctest include directory")
set(TROMPELOEIL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/trompeloeil/include CACHE STRING "Trompeloeil include directory")
set(LEAPSDK_LIB_DIR ${CMAKE_SOURCE_DIR}/external/LeapSDK_v5_gemini/lib CACHE STRING "Leap SDK lib directory")
set(LEAPSDK_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/LeapSDK_v5_gemini/include CACHE STRING "Leap SDK include directory")
set(LEAPSDK_IMPLEMENTATION_DIR ${CMAKE_SOURCE_DIR}/external/LeapSDK_v5_gemini/lib CACHE STRING "Leap SDK implementation directory")
set(REALSENSE_LIB_DIR ${CMAKE_SOURCE_DIR}/external/RealSenseSDK/lib CACHE STRING "RealSense SDK lib directory")
set(REALSENSE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/RealSenseSDK/include CACHE STRING "RealSense SDK include directory")
set(REALSENSE_IMPLEMENTATION_DIR ${CMAKE_SOURCE_DIR}/external/RealSenseSDK/bin CACHE STRING "RealSense SDK implementation directory")

# set(ORBSLAM3_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Thirdparty/ORBSLAM3/include CACHE STRING "ORBSLAM3 include directory")
# set(ORBSLAM3_LIB_DIR ${CMAKE_SOURCE_DIR}/Thirdparty/ORBSLAM3/lib CACHE STRING "ORBSLAM3 lib directory")

# set(OPENCV_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Thirdparty/OpenCV/include CACHE STRING "OpenCV include directory")
# set(OPENCV_LIB_DIR ${CMAKE_SOURCE_DIR}/Thirdparty/OpenCV/lib CACHE STRING "OpenCV lib directory")
# set(OPENCV_IMPLEMENTATION_DIR ${CMAKE_SOURCE_DIR}/Thirdparty/OpenCV/bin CACHE STRING "OpenCV implementation directory")

# set(OPENSSL_LIB_DIR ${CMAKE_SOURCE_DIR}/Thirdparty/OpenSSL-Win64/lib CACHE STRING "OpenSSL lib directory")
# set(OPENSSL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Thirdparty/OpenSSL-Win64/include CACHE STRING "OpenSSL include directory")
# set(OPENSSL_IMPLEMENTATION_DIR ${CMAKE_SOURCE_DIR}/Thirdparty/OpenSSL-Win64/bin CACHE STRING "OpenSSL implementation directory")

# set(Thirdparty_ROOT ${CMAKE_SOURCE_DIR})
# set(DBOW2_LIB_DIR ${CMAKE_SOURCE_DIR}/Thirdparty/DBoW2/lib/Release CACHE STRING "DBOW2 lib directory")

# set(G2O_LIB_DIR ${CMAKE_SOURCE_DIR}/Thirdparty/g2o/build/Release CACHE STRING "g2o lib directory")

# set(PANGOLIN_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Thirdparty/Pangolin CACHE STRING "Pangolin include directory")
# set(PANGOLIN_LIB_DIR ${CMAKE_SOURCE_DIR}/Thirdparty/Pangolin CACHE STRING "Pangolin lib directory")

# set(BOOST_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Thirdparty/boost_1_67_0 CACHE STRING "Boost include directory")
# set(BOOST_LIB_DIR ${CMAKE_SOURCE_DIR}/Thirdparty/boost_1_67_0 CACHE STRING "Boost lib directory")

# set(SOPHUS_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Thirdparty/Sophus CACHE STRING "Sophus include directory")

# set(GLU32_LIB "D:/WSDK/Lib/10.0.19041.0/um/x64/glu32.lib")
# set(OPENGL32_LIB "D:/WSDK/Lib/10.0.19041.0/um/x64/opengl32.lib")

add_subdirectory(northstar)
