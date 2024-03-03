# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.22.1)

# Declares and names the project.

project("egldemo")

set(CPP_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

# include directories
include_directories("${CPP_ROOT}/egl")
include_directories("${CPP_ROOT}/log")
include_directories("${CPP_ROOT}/common")

add_library( # Sets the name of the library.
        egldemo

        # Sets the library as a shared library.
        SHARED
        ${CPP_ROOT}/egl/EglHelper.cpp
        ${CPP_ROOT}/egl/EglThread.cpp
        # Provides a relative path to your source file(s).
        native-lib.cpp)


target_link_libraries( # Specifies the target library.
        egldemo

        # Links the target library to the log library
        # included in the NDK.
        EGL
        GLESv3
        android
        log)