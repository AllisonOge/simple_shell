#include <gtest/gtest.h>
#include "test_myshell.h"
#include <string.h>
#define BUFF_SIZE 1024

TEST(MyShellTest, ExitCode) {
    char buf[BUFF_SIZE];
    int myshell_exit_code, sh_exit_code;


    const char* unknown_cmd = "exit";
    // invoke myshell command with unknown command
    snprintf((char *)buf, BUFF_SIZE, "echo \"%s\" | myshell", unknown_cmd);
    myshell_exit_code = WEXITSTATUS(system(buf));

    //invoke /bin/sh with unknown command
    snprintf((char *)buf, BUFF_SIZE, "/bin/sh -c \"%s\"", unknown_cmd);
    sh_exit_code = WEXITSTATUS(system(buf));

    // check if both exit codes are the same
    EXPECT_EQ(myshell_exit_code, sh_exit_code);
}
