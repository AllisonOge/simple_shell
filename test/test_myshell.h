#pragma once

#define BUFF_SIZE 1024

int exec_pgm(const char *cmd, const char *filepath, const char *errpath);
std::string read_file(const char *filepath);

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