project(divider_tests)

add_subdirectory(lib/googletest)

include_directories(${ASDF_HEADERS_DIR})
include_directories(lib/googletest/googletest/include)

set(SOURCE_FILES main.cpp src/test_asdf_c.cpp src/test_asdf_cxx.cpp)

SET(CMAKE_INSTALL_RPATH ${ASDF_INSTALL_BIN_DIR})

add_executable(asdf_tests ${SOURCE_FILES})
target_link_libraries(asdf_tests asdf gtest)
install(TARGETS asdf_tests DESTINATION bin)
