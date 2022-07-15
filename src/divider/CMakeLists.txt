set(SOURCE_FILES main.cpp)

SET(CMAKE_INSTALL_RPATH ${DIVISIBLE_INSTALL_BIN_DIR})

add_executable(divider ${SOURCE_FILES})

target_link_directories(divider PUBLIC ${DIVISIBLE_INSTALL_BIN_DIR})

target_link_libraries(divider PUBLIC division)
install(TARGETS divider DESTINATION ${DIVISIBLE_INSTALL_BIN_DIR})