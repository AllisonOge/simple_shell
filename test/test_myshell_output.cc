#include <gtest/gtest.h>
#include "test_myshell.h"
#include <string.h>

#define BUFF_SIZE 1024

TEST(MyShellTest, OutputMsg) {
    const char* cmd = "/bin/ls -l";
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
    FILE *myshell_output_file = fopen("/tmp/myshell_output", "r");
    FILE *sh_output_file = fopen("/tmp/sh_output", "r");

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
