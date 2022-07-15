cmake_minimum_required(VERSION 3.2)

set (LIB_SOURCE_FILES
    division.cpp
)

add_library(division SHARED ${LIB_SOURCE_FILES})

target_include_directories(division
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS division DESTINATION ${DIVISIBLE_INSTALL_BIN_DIR})
install(FILES division.h division.hpp DESTINATION ${DIVISIBLE_INSTALL_INCLUDE_DIR})
