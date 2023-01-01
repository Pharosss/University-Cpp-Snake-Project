cmake_minimum_required(VERSION 3.4)
project(Library)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    include/Board.h
    include/Body.h
    include/Entity.h
    include/Food.h
    include/Game.h
    include/Head.h
    include/InputManager.h
    include/Renderer.h
    include/State.h
    src/Board.cpp
    src/Body.cpp
    src/Entity.cpp
    src/Food.cpp
    src/Game.cpp
    src/Head.cpp
    src/InputManager.cpp
    src/State.cpp
    src/Renderer.cpp
)
add_library(Library ${SOURCE_FILES})

#add 'include' directory with header files from 'Library' project to paths
target_include_directories(Library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

#Unit Tests section
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
set(CURSES_USE_NCURSES TRUE)
find_package(Curses REQUIRED)

set(SOURCE_TEST_FILES
        test/master.cpp
        test/StudentTest.cpp
)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
        ${CURSES_INCLUDE_DIR}
)

add_executable (Test ${SOURCE_TEST_FILES})

target_link_libraries(Library
        ${CURSES_LIBRARIES}
)

target_link_libraries (Test
        Library
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
        ${CMAKE_CTEST_COMMAND} -C $<CONFIG> --verbose
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

enable_testing()
add_test(LibraryTest Test)