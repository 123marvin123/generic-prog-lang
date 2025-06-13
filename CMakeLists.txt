cmake_minimum_required(VERSION 3.25)
project(masterthesis_transpiler)

set(CMAKE_CXX_STANDARD 20)
option(ACTIVATE_ASANITIZER "Activate Address Sanitizer" OFF)

include(CTest)

include(cmake/CPM.cmake)

CPMAddPackage(
        NAME nlohmann_json
        URL https://github.com/nlohmann/json/archive/refs/tags/v3.12.0.zip
        URL_HASH SHA256=34660b5e9a407195d55e8da705ed26cc6d175ce5a6b1fb957e701fb4d5b04022
        OPTIONS "JSON_BuildTests OFF"
)

CPMAddPackage(
        NAME antlr4-runtime
        URL https://github.com/antlr/antlr4/archive/refs/tags/4.13.2.zip
        URL_HASH SHA256=42d1268524a9c972f5ca1ad1633372ea02a812ff66c1e992925edea5e5cf9c81
        GIT_TAG 4.13.2
        SOURCE_SUBDIR runtime/Cpp
        OPTIONS "ANTLR_BUILD_CPP_TESTS OFF" "ANTLR_BUILD_SHARED OFF"
)

CPMAddPackage(
        NAME jinja2cpp
        URL https://codeload.github.com/123marvin123/Jinja2Cpp/zip/1a65af0d479517bfff81c8e08b51c8d593f122e2
        OPTIONS "JINJA2CPP_BUILD_TESTS OFF"
        CHECKSUM SHA256=990494782cf57ae8fc5d6ea79812b7cdda1e133ef1e74674bbbe8630608b0f97
)

CPMAddPackage(
        NAME CLI11
        URL "https://github.com/CLIUtils/CLI11/archive/refs/tags/v2.5.0.tar.gz"
        OPTIONS "CLI11_BUILD_EXAMPLES OFF" "CLI11_BUILD_TESTS OFF" "CLI11_BUILD_DOCS OFF"
        CHECKSUM SHA256=17e02b4cddc2fa348e5dbdbb582c59a3486fa2b2433e70a0c3bacb871334fd55
)

CPMAddPackage(
        NAME Catch2
        VERSION 3.8.1
        URL https://codeload.github.com/catchorg/Catch2/tar.gz/refs/tags/v3.8.1
        URL_HASH SHA256=18b3f70ac80fccc340d8c6ff0f339b2ae64944782f8d2fca2bd705cf47cadb79
)

# Find the ANTLR4 executable
find_program(ANTLR_EXECUTABLE antlr)

set(GRAMMAR_FILE ${CMAKE_SOURCE_DIR}/grammar/CongParser.g4)
set(LEXER_FILE ${CMAKE_SOURCE_DIR}/grammar/CongLexer.g4)

if (NOT ANTLR_EXECUTABLE)
    message(WARNING "antlr4 executable not found. We are not able to build grammar files.")

    # Add a custom target that depends on the generated files
    add_custom_target(generate_grammar_files)
else ()
    message(STATUS "Found antlr executable at ${ANTLR_EXECUTABLE}")

    add_custom_command(
            OUTPUT ${CMAKE_SOURCE_DIR}/generated/CongLexer.cpp ${CMAKE_SOURCE_DIR}/generated/CongParser.cpp
            COMMAND ${ANTLR_EXECUTABLE} -no-listener -visitor -Dlanguage=Cpp -o ${CMAKE_SOURCE_DIR}/generated
            ${LEXER_FILE} ${GRAMMAR_FILE}
            DEPENDS ${LEXER_FILE} ${GRAMMAR_FILE}
            COMMENT "Generating ANTLR lexer and parser from ${GRAMMAR_FILE}"
    )

    # Add a custom target that depends on the generated files
    add_custom_target(generate_grammar_files
            DEPENDS ${CMAKE_SOURCE_DIR}/generated/CongLexer.cpp ${CMAKE_SOURCE_DIR}/generated/CongParser.cpp
    )
endif ()

# When we are building in debug mode, add address sanitizer option
if (CMAKE_BUILD_TYPE STREQUAL "Debug" AND ACTIVATE_ASANITIZER)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=address")
endif ()

file(GLOB_RECURSE SRC_FILES LIST_DIRECTORIES false ${CMAKE_SOURCE_DIR}/src/**/*.cpp ${CMAKE_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM SRC_FILES ${CMAKE_SOURCE_DIR}/src/main.cpp)
add_executable(masterthesis_transpiler ${SRC_FILES} ${CMAKE_SOURCE_DIR}/src/main.cpp)

# Ensure the grammar files are generated before building the executable
add_dependencies(masterthesis_transpiler generate_grammar_files)

# Link the ANTLR4 runtime library
target_link_libraries(masterthesis_transpiler antlr4_static nlohmann_json jinja2cpp CLI11)

target_include_directories(masterthesis_transpiler PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/generated
        ${CMAKE_SOURCE_DIR}/libs/termcolor
)

target_sources(masterthesis_transpiler PRIVATE ${CMAKE_SOURCE_DIR}/generated/CongLexer.cpp
        ${CMAKE_SOURCE_DIR}/generated/CongParser.cpp)

file(GLOB_RECURSE TEST_FILES ${CMAKE_SOURCE_DIR}/test/**/*.cpp ${CMAKE_SOURCE_DIR}/test/*.cpp)
foreach (TEST_FILE ${TEST_FILES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_FILE} ${SRC_FILES})
    target_link_libraries(${TEST_NAME} antlr4_static nlohmann_json Catch2::Catch2WithMain jinja2cpp CLI11)
    target_include_directories(${TEST_NAME} PRIVATE
            ${CMAKE_SOURCE_DIR}/include
            ${CMAKE_SOURCE_DIR}/libs/termcolor
            ${CMAKE_SOURCE_DIR}/generated)

    # Suppress "ignored attributes" warnings
    target_compile_options(${TEST_NAME} PRIVATE -Wno-ignored-attributes)

    # Add the generated files to the executable
    target_sources(${TEST_NAME} PRIVATE
            ${CMAKE_SOURCE_DIR}/generated/CongLexer.cpp
            ${CMAKE_SOURCE_DIR}/generated/CongParser.cpp
    )

    target_compile_definitions(${TEST_NAME} PRIVATE
        __CATCH2_TEST__
    )
    add_dependencies(${TEST_NAME} generate_grammar_files)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME} --order rand --warn NoAssertions -d yes)
endforeach ()
