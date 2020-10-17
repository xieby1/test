macro(add_custom_test name)
    add_test(
        NAME test_${name}
        COMMAND $ENV{TEST_CMD_PRE} ${name}
        )
endmacro()

macro(add_executables_and_tests)
    foreach(name ${ARGV})
        add_executable(
            ${name}
            ${name}.c)
        add_custom_test(${name})
    endforeach()
endmacro()

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
        add_custom_test(${name})
    endforeach()
endmacro()
