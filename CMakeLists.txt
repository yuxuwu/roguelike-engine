cmake_minimum_required(VERSION 3.17)
project(roguelike_engine)

set(CMAKE_CXX_STANDARD 14)



set(SOURCE_FILES
        WinMain.cpp
        GameWindow.cpp
        GameGraphics.cpp

        DungeonMap.cpp

        utils/FileHandling.cpp
        utils/WindowsErrorHandling.cpp
        )
add_executable(roguelike_engine WIN32 ${SOURCE_FILES})



add_subdirectory("googletest")
include_directories("googletest/googletest/include")
include_directories("googletest/googlemock/include")

set(TEST_FILES
        tests/Tests.cpp
        tests/utils/WindowsErrorHandlingTest.cpp
        )
add_executable(unit_tests ${SOURCE_FILES} ${TEST_FILES})
add_custom_target(copy_testfiles
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/testfiles
        ${CMAKE_CURRENT_BINARY_DIR}/testfiles
        )
add_dependencies(unit_tests copy_testfiles)
target_link_libraries(unit_tests LINK_PUBLIC gtest_main gtest)