#pragma once

int exec_pgm(const char *cmd, const char *filepath, const char *errpath);

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