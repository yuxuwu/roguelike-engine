cmake_minimum_required(VERSION 3.17)
project(roguelike_engine)

set(CMAKE_CXX_STANDARD 14)



set(SOURCE_FILES
        pch.cpp
        WinMain.cpp
        GameWindow.cpp
        DungeonMap.cpp

        graphics/GameGraphics.cpp
        graphics/Shader.cpp
        graphics/RenderingTarget.cpp
        graphics/Vertices.cpp

        error_handling/FileHandling.cpp
        error_handling/WindowsErrorHandling.cpp)
add_executable(roguelike_engine WIN32 ${SOURCE_FILES})



add_subdirectory("googletest")
include_directories("googletest/googletest/include")
include_directories("googletest/googlemock/include")

set(TEST_FILES
        Tests.cpp
        error_handling/WindowsErrorHandlingTest.cpp
        )
add_executable(unit_tests ${SOURCE_FILES} ${TEST_FILES})
add_custom_target(copy_testfiles
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/testfiles
        ${CMAKE_CURRENT_BINARY_DIR}/testfiles
        )
add_dependencies(unit_tests copy_testfiles)
target_link_libraries(unit_tests LINK_PUBLIC gtest_main gtest)
add_dependencies(roguelike_engine copy_testfiles)