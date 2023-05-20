#include <gtest/gtest.h>
#include <libgen.h>
#include <string.h>
#define BUFF_SIZE 1024

int exec_pgm(const char *cmd, const char *filepath, const char *errpath){
    char buf[BUFF_SIZE];

    snprintf((char *)buf, BUFF_SIZE, "%s > %s 2> %s", cmd, filepath, errpath);
    return WEXITSTATUS(system(buf));
}

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

    // check if both exit codes are the same
    EXPECT_EQ(myshell_exit_code, sh_exit_code);
}

TEST(MyShellTest, ErrorMsg) {
    const char* cmd = "unknown_command";
    char buf[BUFF_SIZE];
    // char *myshell_output = nullptr, *sh_output = nullptr;
    std::string myshell_output_str, sh_output_str;
    int myshell_exit_code, sh_exit_code;

    // invoke myshell command with unknown command
    snprintf((char *)buf, BUFF_SIZE, "echo \"%s\" | myshell", cmd);
    myshell_exit_code = exec_pgm(buf, "/tmp/myshell_output", "/tmp/myshell_error");

    // invoke /bin/sh with unknown command
    snprintf((char *)buf, BUFF_SIZE, "/bin/sh -c \"%s\"", cmd);
    sh_exit_code = exec_pgm(buf, "/tmp/sh_output", "/tmp/sh_error");

    // open the output files
    FILE *myshell_output_file = fopen("/tmp/myshell_error", "r");
    FILE *sh_output_file = fopen("/tmp/sh_error", "r");

    // compare the output files
    while (fgets(buf, BUFF_SIZE, myshell_output_file) != NULL) {
        // myshell_output = strdup(buf);
        myshell_output_str += buf;
    }
    while (fgets(buf, BUFF_SIZE, sh_output_file) != NULL) {
        // sh_output = strdup(buf);
        sh_output_str += buf;
    }

    // close the output files
    fclose(myshell_output_file);
    fclose(sh_output_file);

    // check if both exit codes are the same
    EXPECT_EQ(myshell_exit_code, sh_exit_code);
    // check if both error messages are the same
    EXPECT_STREQ(myshell_output_str.c_str(), sh_output_str.c_str());

}
