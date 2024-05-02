#ifndef BASE_EXCEPTION_H
#define BASE_EXCEPTION_H

#include <exception>

class BaseException : public std::exception {
public:
    BaseException(const char* time, const char* fileName, size_t line, const char* className,
                  const char* methodName, const char* info);
    [[nodiscard]] const char* what() const noexcept override;

protected:
    char errInfo[1024]{};
};

#endif
