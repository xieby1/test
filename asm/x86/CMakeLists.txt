enable_language(ASM)
enable_testing()

set(SOURCE_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../..)
include(${SOURCE_ROOT}/common.cmake)

set(bare_asms
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

add_bare_asms_and_tests(${bare_asms})

foreach(name ${bare_asms})
    set_property(
        TEST test_${name}
        PROPERTY
            LABELS 
                "\
                goal_test;\
                arch_x86;\
                lang_asm;\
                "
        )
endforeach()
