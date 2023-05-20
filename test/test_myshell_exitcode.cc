#include <gtest/gtest.h>
#include "test_myshell.h"
#include <string.h>

TEST(MyShellTest, ExitCode) {
    char buf[BUFF_SIZE];
    int myshell_exit_code, sh_exit_code;


    const char* unknown_cmd = "unknwon_cmd";
    // invoke myshell command with unknown command
    snprintf((char *)buf, BUFF_SIZE, "echo \"%s\" | myshell", unknown_cmd);
    myshell_exit_code = WEXITSTATUS(system(buf));

    //invoke /bin/sh with unknown command
    snprintf((char *)buf, BUFF_SIZE, "/bin/sh -c \"%s\"", unknown_cmd);
    sh_exit_code = WEXITSTATUS(system(buf));

    // check if both exit codes are the same
    EXPECT_EQ(myshell_exit_code, sh_exit_code);
}

TEST(MyShellTest, ExitCode2) {
    char buf[BUFF_SIZE];
    int myshell_exit_code, sh_exit_code;


    const char* exitcmd = "exit";
    // invoke myshell command with unknown command
    snprintf((char *)buf, BUFF_SIZE, "echo \"%s\" | myshell", exitcmd);
    myshell_exit_code = WEXITSTATUS(system(buf));

    //invoke /bin/sh with unknown command
    snprintf((char *)buf, BUFF_SIZE, "/bin/sh -c \"%s\"", exitcmd);
    sh_exit_code = WEXITSTATUS(system(buf));

    // check if both exit codes are the same
    EXPECT_EQ(myshell_exit_code, sh_exit_code);
}
