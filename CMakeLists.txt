cmake_minimum_required(VERSION 3.10)
project(MetaLang CXX C)

cmake_policy(SET CMP0135 NEW)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(META_LANG_BUILD_TESTS "Whether to build tests" OFF)

include(FetchContent)

# add test resources file path
macro(meta_lang_test_res_def target var filename)
    get_filename_component(_TMP_F ${filename} ABSOLUTE)
    message(STATUS "Adding resource file path for target ${target} ${var}=\"${_TMP_F}\"")
    target_compile_definitions(${target} PUBLIC "${var}=\"${_TMP_F}\"")
    unset(_TMP_F)
endmacro()

# meta grammar parser for itself
file(GLOB_RECURSE _meta_lang_parser_src meta_lang/src/parser/*.cc)
message(STATUS "Adding sources ${_meta_lang_parser_src}")
add_library(meta_grammar_parser STATIC ${_meta_lang_parser_src})
target_include_directories(meta_grammar_parser PUBLIC meta_lang/)

if (META_LANG_BUILD_TESTS)
    # setup google test
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    enable_testing()
    include(GoogleTest)

    # helper for adding a test
    macro(meta_lang_test name)
        add_executable(${name} ${ARGN})
        target_link_libraries(${name} PRIVATE GTest::gtest_main)
        target_include_directories(${name} PUBLIC meta_lang/)
        target_link_libraries(${name} PUBLIC meta_grammar_parser)
        gtest_discover_tests(${name})
    endmacro()

    meta_lang_test(test_utf8 meta_lang/test/util/string/test_utf8.cc)
    meta_lang_test(test_lexer meta_lang/test/parser/test_lexer.cc)
endif ()
