// Copyright (c) miliyip, https://github.com/miloyip.
//
// Author:  xianhui (definezxh@163.com)
// Date:    2018/08/03 11:07:32

#include "lept.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format) \
	do { \
		test_count++; \
		if (equality) \
			test_pass++; \
		else { \
			fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual); \
			main_ret = 1; \
		} \
	} while (0)

#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")
#define EXPECT_EQ_DOUBLE(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%17.g")

static void test_parse_null()
{
        lept_value v;
        v.type = LEPT_FALSE;
        EXPECT_EQ_INT(LEPT_PARSE_OK, lept_parse(&v, "null"));
        EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));
}

static void test_parse_true()
{
        lept_value v;
        v.type = LEPT_NULL;
        EXPECT_EQ_INT(LEPT_PARSE_OK, lept_parse(&v, "true"));
        EXPECT_EQ_INT(LEPT_TRUE, lept_get_type(&v));
}

static void test_parse_false()
{
        lept_value v;
        v.type = LEPT_NULL;
        EXPECT_EQ_INT(LEPT_PARSE_OK, lept_parse(&v, "false"));
        EXPECT_EQ_INT(LEPT_FALSE, lept_get_type(&v));
}

#define TEST_NUMBER(expect, json) \
	do { \
		lept_value v; \
		v.type = LEPT_NULL; \
		EXPECT_EQ_INT(LEPT_PARSE_OK, lept_parse(&v, json)); \
		EXPECT_EQ_INT(LEPT_NUMBER, lept_get_type(&v)); \
		EXPECT_EQ_DOUBLE(expect, lept_get_number(&v)); \
	} while (0)

static void test_parse_number()
{
        // int
        TEST_NUMBER(0.0, "0");
        TEST_NUMBER(0.0, "-0");
        TEST_NUMBER(1.0, "1");
        TEST_NUMBER(-1.0, "-1");
        TEST_NUMBER(12.0, "12");

        // int frac
        TEST_NUMBER(0.0, "0.0");
        TEST_NUMBER(-0.0, "-0.0");
        TEST_NUMBER(1.1, "1.1");
        TEST_NUMBER(-1.1, "-1.1");
        TEST_NUMBER(1.0, "1.000");
        TEST_NUMBER(11.101, "11.101");

        // int exp
        TEST_NUMBER(0.0, "0e10");
        TEST_NUMBER(0.0, "-0e10");
        TEST_NUMBER(100.0, "1e2");
        TEST_NUMBER(100.0, "1E2");
        TEST_NUMBER(100.0, "1e+2");
        TEST_NUMBER(100.0, "1E+2");

        // int frac exp
        TEST_NUMBER(10.0, "1.0e1");
        TEST_NUMBER(-10.0, "-1.0e1");
        TEST_NUMBER(10.0, "1.0e+1");
        TEST_NUMBER(10.0, "1.0E1");
        TEST_NUMBER(10.0, "1.0E+1");
        TEST_NUMBER(0.1, "1.0e-1");
        TEST_NUMBER(-0.1, "-1.0e-1");
        TEST_NUMBER(0.1, "1.0E-1");
}

static void test_parse_expect_value()
{
        lept_value v;

        v.type = LEPT_FALSE;
        EXPECT_EQ_INT(LEPT_PARSE_EXPECT_VALUE, lept_parse(&v, ""));
        EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));

        v.type = LEPT_FALSE;
        EXPECT_EQ_INT(LEPT_PARSE_EXPECT_VALUE, lept_parse(&v, " "));
        EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));
}

static void test_parse_invalid_value()
{
        lept_value v;

        v.type = LEPT_FALSE;
        EXPECT_EQ_INT(LEPT_PARSE_INVALID_VALUE, lept_parse(&v, "nul"));
        EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));

        v.type = LEPT_FALSE;
        EXPECT_EQ_INT(LEPT_PARSE_INVALID_VALUE, lept_parse(&v, "?"));
        EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));
}

void test()
{
        test_parse_null();
        test_parse_true();
        test_parse_false();
        test_parse_number();
        test_parse_expect_value();
        test_parse_invalid_value();
}

int main()
{
        test();
        printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
}
