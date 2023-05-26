#include <gtest/gtest.h>
#include "test_myshell.h"
#include <string.h>

TEST(MyShellTest, NoENV) {
    const char* cmd = "ls -l";
    char buf[BUFF_SIZE];
    // get path myshell path
    std::string shellpath = get_shell_path();
    std::string myshell_output_str, sh_output_str;
    std::string myshell_error_str, sh_error_str;
    int myshell_exit_code, sh_exit_code;

    // unset PATH enviroment variable
    printf("shellpath: %s\n", shellpath.c_str());
    setenv("PATH", shellpath.c_str(), 1);
    printf("PATH: %s\n", getenv("PATH"));
    // invoke myshell command with unknown command
    snprintf((char *)buf, BUFF_SIZE, "echo \"%s\" | myshell", cmd);
    myshell_exit_code = exec_pgm(buf, "/tmp/myshell_output", "/tmp/myshell_error");

    // invoke /bin/sh with unknown command
    snprintf((char *)buf, BUFF_SIZE, "/bin/sh -c \"%s\"", cmd);
    sh_exit_code = exec_pgm(buf, "/tmp/sh_output", "/tmp/sh_error");

    // read output and error files
    myshell_output_str = read_file("/tmp/myshell_output");
    myshell_error_str = read_file("/tmp/myshell_error");
    sh_output_str = read_file("/tmp/sh_output");
    sh_error_str = read_file("/tmp/sh_error");

    // check if both exit codes are the same
    EXPECT_EQ(myshell_exit_code, sh_exit_code);
    // check if both output messages are the same
    EXPECT_STREQ(myshell_output_str.c_str(), sh_output_str.c_str());
}
