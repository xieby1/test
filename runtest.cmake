execute_process(
    COMMAND
        $ENV{TEST_CMD_PRE}
        ${TEST_EXECUTABLE}
        $ENV{TEST_CMD_SUF}
    RESULT_VARIABLE
        result
    )
if(NOT "${result}" STREQUAL "0")
    message(
        FATAL_ERROR
            "Test failed with return value '${result}'"
        )
endif()
