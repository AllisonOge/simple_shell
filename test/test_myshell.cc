#include <gtest/gtest.h>
#include "test_myshell.h"
#include <string.h>
#define BUFF_SIZE 1024

int exec_pgm(const char *cmd, const char *filepath, const char *errpath){
    char buf[BUFF_SIZE];

    snprintf((char *)buf, BUFF_SIZE, "%s > %s 2> %s", cmd, filepath, errpath);
    return WEXITSTATUS(system(buf));
}

std::string read_file(const char *filepath){
    char buf[BUFF_SIZE];
    std::string str;
    FILE *file = fopen(filepath, "r");

    while (fgets(buf, BUFF_SIZE, file) != NULL) {
        str += buf;
    }
    fclose(file);
    return str;
}
