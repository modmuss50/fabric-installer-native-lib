cmake_minimum_required(VERSION 3.17)
project(fabric_installer_native_lib)

set(CMAKE_CXX_STANDARD 20)

set(NATIVE_SOURCE linux.cpp) # The source file to be build against the header
set(NATIVE_JNI linux) # The platform specific JNI sub directory
IF(APPLE)
    set(NATIVE_SOURCE macos.mm)
    set(NATIVE_JNI darwin)

    SET(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "Build architectures for Mac OS X" FORCE)
ELSEIF (WIN32)
    set(NATIVE_SOURCE windows.cpp)
    set(NATIVE_JNI win32)
ENDIF()

message(STATUS "JAVA_HOME= $ENV{JAVA_HOME}")

set(JAVA_INCLUDE_PATH $ENV{JAVA_HOME}/include)
set(JAVA_INCLUDE_PATH2 $ENV{JAVA_HOME}/include/${NATIVE_JNI})

find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})

add_library(fabric_installer_native_lib SHARED MojangLauncherHelper.h ${NATIVE_SOURCE})

IF(APPLE)
    target_link_libraries(fabric_installer_native_lib "-framework AppKit")
ENDIF()