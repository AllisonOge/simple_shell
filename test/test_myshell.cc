#include <gtest/gtest.h>
#include <libgen.h>
#include <string.h>
#define BUFF_SIZE 1024

class MyShellTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }
};

TEST(MyShellTest, ExitCode) {
    char buf[BUFF_SIZE];
    int myshell_exit_code, sh_exit_code;


    const char* unknown_cmd = "unknown_command";
    // invoke myshell command with unknown command
    snprintf((char *)buf, BUFF_SIZE, "echo \"%s\" | myshell", unknown_cmd);
    myshell_exit_code = WEXITSTATUS(system(buf));

    //invoke /bin/sh with unknown command
    snprintf((char *)buf, BUFF_SIZE, "/bin/sh -c \"%s\"", unknown_cmd);
    sh_exit_code = WEXITSTATUS(system(buf));

    printf("myshell exit code: %d -> sh exit code: %d\n", myshell_exit_code, sh_exit_code);
    // check if both exit codes are the same
    EXPECT_EQ(myshell_exit_code, sh_exit_code);
}
