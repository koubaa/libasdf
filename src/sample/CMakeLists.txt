set(SOURCE_FILES main.cpp)

SET(CMAKE_INSTALL_RPATH ${ASDF_INSTALL_BIN_DIR})

add_executable(sample ${SOURCE_FILES})

target_link_directories(sample PUBLIC ${ASDF_INSTALL_BIN_DIR})

target_link_libraries(sample PUBLIC asdf)
install(TARGETS sample DESTINATION ${ASDF_INSTALL_BIN_DIR})