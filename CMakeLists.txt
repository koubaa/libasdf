cmake_minimum_required(VERSION 3.17)

project(asdf C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(ASDF_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(ASDF_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(ASDF_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

set(ASDF_HEADERS_DIR ${PROJECT_SOURCE_DIR}/src/asdf)

include_directories(${ASDF_INSTALL_INCLUDE_DIR})
include_directories(${ASF_HEADERS_DIR})

add_subdirectory(src)
add_subdirectory(test)


