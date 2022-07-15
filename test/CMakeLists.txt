project(divider_tests)

add_subdirectory(lib/googletest)

include_directories(${DIVISION_HEADERS_DIR})
include_directories(lib/googletest/googletest/include)

set(SOURCE_FILES main.cpp src/test_divider_c.cpp src/test_divider_cxx.cpp)

SET(CMAKE_INSTALL_RPATH ${DIVISIBLE_INSTALL_BIN_DIR})

add_executable(divider_tests ${SOURCE_FILES})
target_link_libraries(divider_tests division gtest)
install(TARGETS divider_tests DESTINATION bin)
