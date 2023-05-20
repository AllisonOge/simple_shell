# add gtest source folder (provide gtests and gtest_main)
add_subdirectory(/usr/src/gtest
                ${PROJECT_BINARY_DIR}/gtest)

# include CTest package
include(CTest)

# add a function to create test executables
function(add_test_executable TEST_NAME TEST_SOURCES)
    add_executable(${TEST_NAME} ${TEST_SOURCES} test_myshell.cc)
    target_link_libraries(${TEST_NAME} 
            gtest gtest_main)
endfunction()

if (ENABLE_VALGRIND)
    set(VALGRIND_EXECUTABLE "/usr/bin/valgrind" CACHE STRING "Valgrind executable")
    find_program(VALGRIND "valgrind")
    if (VALGRIND)
        set(VALGRIND_OPTIONS "valgrind --leak-check=full --error-exitcode=1")
        separate_arguments(VALGRIND_OPTIONS)
        # create test executable
        add_test_executable(test_myshell_exitcode test_myshell_exitcode.cc)
        add_test_executable(test_myshell_error test_myshell_errormsg.cc)

        # add test
        add_test(NAME ExitCode 
                COMMAND ${VALGRIND} ${VALGRIND_OPTIONS} ${CMAKE_CURRENT_BINARY_DIR}/test_myshell_exitcode)
        add_test(NAME ErrorMsg 
                COMMAND ${VALGRIND} ${VALGRIND_OPTIONS} ${CMAKE_CURRENT_BINARY_DIR}/test_myshell_error)

        # set PATH to find myshell
        set_tests_properties(ExitCode ErrorMsg PROPERTIES ENVIRONMENT "PATH=${CMAKE_BINARY_DIR}:$ENV{PATH}")
    else()
        message(FATAL_ERROR "Valgrind not found")
    endif()
endif()
