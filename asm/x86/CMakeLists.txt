enable_language(ASM)
enable_testing()

# Here "bare asm" means the asm does't need link against default libs,
# as the bare asm has defined _start symbol.
macro(add_bare_asms_and_tests)
    foreach(name ${ARGV})
        add_executable(${name} ${name}.s)
        set_target_properties(
            ${name}
            PROPERTIES
            COMPILE_OPTIONS "-m32;"
            LINK_OPTIONS "-m32;-nostdlib;"
            )
        add_test(
            NAME test_${name}
            COMMAND ${name}
            )
    endforeach()
endmacro()

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
