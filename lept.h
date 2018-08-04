// Copyright (c) milo yip, https://github.com/miloyip.
//
// Author:  xianhui (definezxh@163.com)
// Date:    2018/08/03 09:43:57

#ifndef LEPT_H
#define LEPT_H

typedef enum {
        LEPT_NULL,
        LEPT_FALSE,
        LEPT_TRUE,
        LEPT_NUMBER,
        LEPT_STRING,
        LEPT_ARRAY,
        LEPT_OBJECT
} lept_type;

typedef struct {
        lept_type type;
        double number;
} lept_value;

enum {
        LEPT_PARSE_OK = 0,
        LEPT_PARSE_EXPECT_VALUE,
        LEPT_PARSE_INVALID_VALUE,
        LEPT_PARSE_ROOT_NOT_SINGULAR,
        LEPT_PARSE_NUMBER_TOO_BIG
};

int lept_parse(lept_value* v, const char* json);

lept_type lept_get_type(const lept_value* v);

double lept_get_number(const lept_value* v);

#endif	// LEPT_H
