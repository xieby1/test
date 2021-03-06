cmake_minimum_required(VERSION 3.16)
enable_testing()

set(SOURCE_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../..)
include(${SOURCE_ROOT}/common.cmake)

add_executables_and_tests(
    override
    move
    shared_writable_4x4k_page
    4x4k_pages_access_prot
    )

set_target_properties(
    shared_writable_4x4k_page
    4x4k_pages_access_prot
    PROPERTIES
    COMPILE_OPTIONS "-g;-m32"
    LINK_OPTIONS "-m32"
    INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR};${SOURCE_ROOT}/include;"
    LINK_LIBRARIES "rt"
    )

set_tests_properties(
    test_shared_writable_4x4k_page
    test_4x4k_pages_access_prot
    PROPERTIES
        LABELS "\
            goal_test;\
            arch_x86;\
            lang_c;\
            "
    )

set_tests_properties(
    test_override
    test_move
    PROPERTIES
        LABELS "\
            goal_learn;\
            arch_all;\
            lang_c;\
            "
    )
