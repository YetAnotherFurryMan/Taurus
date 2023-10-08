cmake_minimum_required(VERSION 3.7)

project(trs VERSION 1.0.0 LANGUAGES CXX)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

add_subdirectory(core)

add_subdirectory(test)
