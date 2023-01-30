cmake_minimum_required(VERSION 3.4)
project(Library)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        include/entities/Body.h
        include/entities/Entity.h
        include/entities/Food.h
        include/entities/Head.h

        include/game/Board.h
        include/game/Game.h
        include/game/State.h
        
        include/io/CLIReader.h
        include/io/FileIO.h
        include/io/Input.h
        include/io/InputManager.h
        include/io/Renderer.h

        src/entities/Body.cpp
        src/entities/Entity.cpp
        src/entities/Food.cpp
        src/entities/Head.cpp

        src/game/Board.cpp
        src/game/Game.cpp
        src/game/State.cpp
        
        src/io/CLIReader.cpp
        src/io/FileIO.cpp
        src/io/InputManager.cpp
        src/io/Renderer.cpp
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
        test/BoardTest.cpp
        test/BodyTest.cpp
        test/GameTest.cpp
        test/HeadTest.cpp
        test/StateTest.cpp
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