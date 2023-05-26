#include <gtest/gtest.h>
#include "test_myshell.h"
#include <string.h>

TEST(MyShellTest, Default) {
    const char* cmd = "cd\n/bin/pwd";
    char buf[BUFF_SIZE];
    std::string myshell_output_str, sh_output_str;
    std::string myshell_error_str, sh_error_str;
    int myshell_exit_code, sh_exit_code;

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
    // check if both error messages are the same
    EXPECT_STREQ(myshell_error_str.c_str(), sh_error_str.c_str());
}

TEST(MyShellTest, CdRootWithoutPermission) {
    const char* cmd = "cd /root\n/bin/pwd";
    char buf[BUFF_SIZE];
    std::string myshell_output_str, sh_output_str;
    std::string myshell_error_str, sh_error_str;
    int myshell_exit_code, sh_exit_code;

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

TEST(MyShellTest, CdWithoutHOME) {
    const char* cmd = "cd\n/bin/pwd";
    char buf[BUFF_SIZE];
    std::string myshell_output_str, sh_output_str;
    std::string myshell_error_str, sh_error_str;
    int myshell_exit_code, sh_exit_code;

    // remove HOME environment variable
    setenv("HOME", "", 1);
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

TEST(MyShellTest, CdSpecialWithoutOLDPWD) {
    const char* cmd = "cd -\n/bin/pwd";
    char buf[BUFF_SIZE];
    std::string myshell_output_str, sh_output_str;
    std::string myshell_error_str, sh_error_str;
    int myshell_exit_code, sh_exit_code;

    // remove OLDPWD environment variable
    setenv("OLDPWD", "", 1);
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

TEST(MyShellTest, CdThreeTimes) {
    const char* cmd = "cd /tmp\ncd /dev\ncd -\n/bin/pwd";
    char buf[BUFF_SIZE];
    std::string myshell_output_str, sh_output_str;
    std::string myshell_error_str, sh_error_str;
    int myshell_exit_code, sh_exit_code;

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