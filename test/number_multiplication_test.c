#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmocka.h>

#include "number_multiplication.h"

static void perform_multiply_test(const char* const a, const char* const b, const char* const expected)
{
    char* result = multiply((char*)a, (char*)b);
    assert_string_equal(result, expected);
    free(result);
}

/* A test case that does nothing and succeeds. */
static void null_test_success(void **state)
{
    (void) state; /* unused */

    perform_multiply_test("0", "0", "0");
    perform_multiply_test("0", "1", "0");
    perform_multiply_test("1", "0", "0");
    perform_multiply_test("1", "1", "1");
    perform_multiply_test("5", "6", "30");
    perform_multiply_test("123", "456", "56088");
    perform_multiply_test("999", "999", "998001");
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(null_test_success),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
