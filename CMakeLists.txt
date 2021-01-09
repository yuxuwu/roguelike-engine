cmake_minimum_required(VERSION 3.17)
project(roguelike_engine)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory("googletest")
include_directories("googletest/googletest/include")
include_directories("googletest/googlemock/include")

add_executable(roguelike_engine WIN32 WinMain.cpp)
add_executable(unit_tests Tests.cpp)

target_link_libraries(unit_tests LINK_PUBLIC gtest_main gtest)

add_custom_target(copy_testfiles
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/testfiles ${CMAKE_CURRENT_BINARY_DIR}/testfiles
)
add_dependencies(copy_testfiles unit_tests)