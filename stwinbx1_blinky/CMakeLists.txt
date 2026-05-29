# CMakeLists.txt for Zephyr Application
# This file is used by CMake to configure the build environment.

cmake_minimum_required(VERSION 3.20.0)

# Find the Zephyr package. This sets up the compiler, linker, include paths,
# and pulls in all selected drivers and software subsystems.
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

# Declare the name of the executable project.
project(stwinbx1_blinky)

# Specify which C source files to compile.
target_sources(app PRIVATE src/main.c)
