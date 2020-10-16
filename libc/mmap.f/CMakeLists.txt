cmake_minimum_required(VERSION 3.16)

add_executable(
    override
    override.c
    )
add_executable(
    move
    move.c
    )
add_executable(
    shared_writable_4x4k_page
    shared_writable_4x4k_page.c
    )
add_executable(
    4x4k_pages_access_prot
    4x4k_pages_access_prot.c
    )

set_target_properties(
    shared_writable_4x4k_page
    4x4k_pages_access_prot
    PROPERTIES
    COMPILE_OPTIONS "-g;-m32"
    LINK_OPTIONS "-m32"
    INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR};${CMAKE_CURRENT_SOURCE_DIR}/../../include"
    LINK_LIBRARIES "rt"
    )
