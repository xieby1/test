enable_language(ASM)
enable_testing()

set(SOURCE_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../..)
include(${SOURCE_ROOT}/common.cmake)

add_bare_asms_and_tests(
    aaa
    conditionalCode
    cpuid
    lddqu
    movbe
    movsldup
    pextrb
    pinsrb
    vmovss
    writeMemNoPrint
    writeMem
    )
