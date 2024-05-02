#include "../inc/base_exception.h"

extern "C" {
#include <stdlib.h>
#include <string.h>
}

#include <string>

BaseException::BaseException(const char *time, const char *fileName, size_t line, const char *className,
                             const char *methodName, const char *info) {
    strcpy(errInfo, "");
    strcat(errInfo, "\nFile name: ");
    strcat(errInfo, fileName);
    strcat(errInfo, "\nClass: ");
    strcat(errInfo, className);
    strcat(errInfo, "\nMethod: ");
    strcat(errInfo, methodName);
    char str_line[10] = "\0";
    strcat(str_line, std::to_string(line).c_str());
    strcat(errInfo, "\nLine: ");
    strcat(errInfo, str_line);
    strcat(errInfo, "\nTime: ");
    strcat(errInfo, time);
    strcat(errInfo, "\nERROR: ");
    strcat(errInfo, info);
}

const char *BaseException::what() const noexcept { return errInfo; }
