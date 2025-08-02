cmake_minimum_required(VERSION 3.16)
project(GovInterpreter VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_DIR "${CMAKE_SOURCE_DIR}/build")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}/bin)
set(CMAKE_BINARY_DIR ${BUILD_DIR})

set(SOURCES
    src/main.cpp
    src/lexer.cpp
    src/parser.cpp
    src/interpreter.cpp
)

set(HEADERS
    src/lexer.h
    src/parser.h
    src/interpreter.h
)

add_executable(gov ${SOURCES} ${HEADERS})

set_target_properties(gov PROPERTIES
    OUTPUT_NAME "gov"
    RUNTIME_OUTPUT_DIRECTORY "${BUILD_DIR}/bin"
)

if(WIN32)
    set_target_properties(gov PROPERTIES
        OUTPUT_NAME "gov"
        SUFFIX ".exe"
    )
endif()

if(MSVC)
    target_compile_options(gov PRIVATE /W4)
else()
    target_compile_options(gov PRIVATE -Wall -Wextra -Wpedantic)
endif()

install(TARGETS gov
    RUNTIME DESTINATION bin
)

message(STATUS "Building Gov Interpreter")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Output Directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}") 