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

# create test executable
add_test_executable(test_myshell_exitcode test_myshell_exitcode.cc)
add_test_executable(test_myshell_error test_myshell_errormsg.cc)
add_test_executable(test_myshell_output test_myshell_output.cc)
add_test_executable(test_myshell_noenv test_myshell_noenv.cc)

# add test
add_test(NAME ExitCode 
        COMMAND test_myshell_exitcode)
add_test(NAME ErrorMsg 
        COMMAND test_myshell_error)
add_test(NAME OutputMsg 
        COMMAND test_myshell_output)
add_test(NAME NoENV 
        COMMAND test_myshell_noenv)

# set PATH to find myshell
set_tests_properties(ExitCode ErrorMsg OutputMsg NoENV 
        PROPERTIES ENVIRONMENT "PATH=${CMAKE_BINARY_DIR}:$ENV{PATH}")

if (ENABLE_VALGRIND)
    set(VALGRIND_EXECUTABLE "/usr/bin/valgrind" CACHE STRING "Valgrind executable")
    find_program(VALGRIND "valgrind")
    if (VALGRIND)
        set(VALGRIND_OPTIONS "valgrind --leak-check=full --error-exitcode=1")

        separate_arguments(VALGRIND_OPTIONS)

        add_test(NAME ValgrindFullPathWithArgs 
            COMMAND ${VALGRIND} ${VALGRIND_OPTIONS} 
            "/bin/echo" "/bin/ls -l" "|" ${CMAKE_BINARY_DIR}/myshell)
        add_test(NAME ValgrindCmdWithArgs 
            COMMAND ${VALGRIND} ${VALGRIND_OPTIONS} 
            "/bin/echo" "ls -l" "|" ${CMAKE_BINARY_DIR}/myshell)
    else()
        message(FATAL_ERROR "Valgrind not found")
    endif()
endif()
