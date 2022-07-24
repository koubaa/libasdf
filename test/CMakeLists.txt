project(asdf_tests)

include_directories(${ASDF_HEADERS_DIR})

set(SOURCE_FILES main.cpp src/test_asdf_c.cpp src/test_asdf_cxx.cpp)

SET(CMAKE_INSTALL_RPATH ${ASDF_INSTALL_BIN_DIR})

add_executable(asdf_tests ${SOURCE_FILES})
target_link_libraries(asdf_tests asdf)
install(TARGETS asdf_tests DESTINATION bin)
