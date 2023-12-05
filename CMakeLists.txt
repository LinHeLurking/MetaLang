cmake_minimum_required(VERSION 3.10)
project(MetaLang CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
cmake_policy(SET CMP0135 NEW)

option(META_LANG_BUILD_TESTS "Whether to build tests" OFF)

include(FetchContent)

# library helper
macro(meta_lang_library name)
    add_library(${name} ${ARGN})
    target_include_directories(${name} PUBLIC meta_lang/)
endmacro()

# add test resources file path
macro(meta_lang_test_res_def target var filename)
    get_filename_component(_TMP_F ${filename} ABSOLUTE)
    message(STATUS "Adding resource file path for target ${target} ${var}=\"${_TMP_F}\"")
    target_compile_definitions(${target} PUBLIC "${var}=\"${_TMP_F}\"")
    unset(_TMP_F)
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
        target_include_directories(${name} PUBLIC meta_lang/)
        gtest_discover_tests(${name})
    endmacro()

    meta_lang_test(test_meta_grammar meta_lang/test/parser/meta/test_meta_grammar.cc)
    target_link_libraries(test_meta_grammar PUBLIC meta_grammar_parser)
    meta_lang_test_res_def(test_meta_grammar TEST_GRAMMAR_PATH meta_lang/test/parser/meta/)

    meta_lang_test(test_utf8 meta_lang/test/util/string/test_utf8.cc)

    meta_lang_test(test_byte_reader meta_lang/test/util/fs/test_byte_reader.cc)
    meta_lang_test_res_def(test_byte_reader TEST_FILE_PATH meta_lang/test/util/fs/)

    meta_lang_test(test_file_range meta_lang/test/util/fs/test_file_range.cc)
    meta_lang_test_res_def(test_file_range TEST_FILE_PATH meta_lang/test/util/fs/)

    meta_lang_test(test_codepoint_view meta_lang/test/util/string/test_codepoint_view.cc)
    meta_lang_test_res_def(test_codepoint_view TEST_FILE_PATH meta_lang/test/util/string/)
endif ()
