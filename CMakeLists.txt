cmake_minimum_required(VERSION 3.20)
project(MetaLang CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
cmake_policy(SET CMP0135 NEW)

option(META_LANG_BUILD_TESTS "Whether to build tests" OFF)

include(FetchContent)

# library helper
macro(meta_lang_library name)
    add_library(${name} ${ARGN})
    target_include_directories(${name} PRIVATE meta_lang/)
endmacro()

# meta grammar parser for itself
meta_lang_library(meta_grammar_parser STATIC meta_lang/src/parser/meta/meta_grammar.cc)

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
        target_include_directories(${name} PRIVATE meta_lang/)
        gtest_discover_tests(${name})
    endmacro()

    meta_lang_test(test_meta_parser meta_lang/test/parser/meta/test_meta_grammar.cc)
    target_link_libraries(test_meta_parser PRIVATE meta_grammar_parser)

    meta_lang_test(test_utf8 meta_lang/test/util/string/test_utf8.cc)
endif ()
