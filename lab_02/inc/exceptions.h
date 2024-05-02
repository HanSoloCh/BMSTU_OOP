#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "base_exception.h"

// Ошибки вектора
class VectorException : public BaseException {
public:
    VectorException(const char *time, const char *fileName, size_t line, const char *className,
                    const char *methodName, const char *info)
        : BaseException(time, fileName, line, className, methodName, info){};
};

class MemoryException : public VectorException {
public:
    MemoryException(const char *time, const char *fileName, size_t line, const char *className,
                    const char *methodName, const char *info = "Memory allocation error!")
        : VectorException(time, fileName, line, className, methodName, info){};
};

class EmptyVectorException : public VectorException {
public:
    EmptyVectorException(const char *time, const char *fileName, size_t line, const char *className,
                         const char *methodName, const char *info = "Operation with an empty vector!")
        : VectorException(time, fileName, line, className, methodName, info){};
};

class NotEqualSizesException : public VectorException {
public:
    NotEqualSizesException(const char *time, const char *fileName, size_t line, const char *className,
                           const char *methodName,
                           const char *info = "Operation with vectors of different sizes!")
        : VectorException(time, fileName, line, className, methodName, info){};
};

class ZeroVectorException : public VectorException {
public:
    ZeroVectorException(const char *time, const char *fileName, size_t line, const char *className,
                        const char *methodName, const char *info = "Operation with null vector!")
        : VectorException(time, fileName, line, className, methodName, info){};
};

// Ошибки итератора
class IteratorException : public BaseException {
public:
    IteratorException(const char *time, const char *fileName, size_t line, const char *className,
                      const char *methodName, const char *info)
        : BaseException(time, fileName, line, className, methodName, info){};
};

class ExpiredException : public IteratorException {
public:
    ExpiredException(const char *time, const char *fileName, size_t line, const char *className,
                     const char *methodName, const char *info = "Expired weak pointer!")
        : IteratorException(time, fileName, line, className, methodName, info){};
};

class OutOfRangeException : public IteratorException {
public:
    OutOfRangeException(const char *time, const char *fileName, size_t line, const char *className,
                        const char *methodName, const char *info = "Index is out of range!")
        : IteratorException(time, fileName, line, className, methodName, info){};
};

#endif
