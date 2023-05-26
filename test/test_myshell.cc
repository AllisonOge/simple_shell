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

std::string get_shell_path(){
    char buf[BUFF_SIZE];
    FILE *file = popen("pwd", "r");
    std::string str;

    while (fgets(buf, BUFF_SIZE, file) != NULL) {
        str += buf;
    }
    pclose(file);
    str.erase(str.find_last_not_of(" \n\r\t")+1);
    return erase_sub_string(str, "/test");
}

std::string erase_sub_string(std::string & mainStr, const std::string & toErase){
    size_t pos = mainStr.find(toErase);
    if (pos != std::string::npos){
        mainStr.erase(pos, toErase.length());
    }
    return mainStr;
}