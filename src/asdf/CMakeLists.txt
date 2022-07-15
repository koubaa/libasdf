cmake_minimum_required(VERSION 3.2)

set (LIB_SOURCE_FILES
    asdf.cpp
)

add_library(asdf SHARED ${LIB_SOURCE_FILES})

target_include_directories(asdf
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS asdf DESTINATION ${ASDF_INSTALL_BIN_DIR})
install(FILES asdf.h asdf.hpp DESTINATION ${ASDF_INSTALL_INCLUDE_DIR})
