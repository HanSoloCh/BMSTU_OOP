#ifndef ERROR_CODES_H
#define ERROR_CODES_H

typedef enum {
    OK,
    ERR_IO,
    ERR_RANGE,
    ERR_DYN_MEM,
    ERR_FILE,
    UNKNOWN_COMMAND,
    ERR_NO_DATA,
} err_t;

#endif // ERROR_CODES_H
