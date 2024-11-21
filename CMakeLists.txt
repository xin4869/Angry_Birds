cmake_minimum_required(VERSION 3.11.0)
project(angry_birds VERSION 0.1.0)

enable_language(CXX)

# use C++ standard version 17
set(CMAKE_CXX_STANDARD 17)
# produce non-optimized code with debug symbols
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message(STATUS "BUILD directory is ${CMAKE_BINARY_DIR}")
message(STATUS "SRC directory is ${CMAKE_SOURCE_DIR}")

# Add all .c, - files under src/ directory
file(GLOB SOURCES_C "src/*.c")
# Add all .cpp, - files under src/ directory
file(GLOB SOURCES_CPP "src/*.cpp")
# Add all .hpp, - files under src/ directory
file(GLOB SOURCES_HPP "src/*.hpp")
# Add all .h, - files under src/ directory
file(GLOB SOURCES_H "src/*.h")
set(SOURCES ${SOURCES_C} ${SOURCES_CPP} ${SOURCES_H} ${SOURCES_HPP})
message(STATUS "SRC directory source code files: \n\t-- HEADERS: ${SOURCES_H}${SOURCES_HPP}\n\t-- C SOURCES: ${SOURCES_C}\n\t-- CPP SOURCE:${SOURCES_CPP}\n\t-- ALL:${SOURCES}")


link_directories(/opt/homebrew/Cellar/box2d/2.4.2/lib)
include_directories(/opt/homebrew/Cellar/box2d/2.4.2/include)


# Add packages
find_package(box2d 2.4 REQUIRED)
find_package(SFML 2.5 COMPONENTS network audio graphics window system REQUIRED)
find_package(TGUI REQUIRED)

cmake_policy(SET CMP0135 NEW)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


# add the executable target
add_executable(angry_birds)

target_sources(angry_birds PUBLIC ${SOURCES})
target_include_directories(angry_birds PUBLIC .)
target_include_directories(angry_birds PUBLIC src)

target_link_libraries(angry_birds box2d sfml-network sfml-audio sfml-graphics sfml-window sfml-system TGUI::TGUI)

enable_testing()
add_executable(tests "tests/tests.cpp")
target_link_libraries(tests GTest::gtest_main box2d sfml-network sfml-audio sfml-graphics sfml-window sfml-system TGUI::TGUI)

include(GoogleTest)
gtest_discover_tests(tests)

# get a lot of warnings
if(MSVC)
    target_compile_options(angry_birds PRIVATE /Wall)
else()
    # gcc and clang
    target_compile_options(angry_birds PRIVATE -Wall -Wextra -pedantic -Wno-missing-field-initializers)
endif()