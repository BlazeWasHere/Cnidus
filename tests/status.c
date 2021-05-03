//          Copyright Blaze 2021.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

// CMOCKA DEPS...
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
// END CMOCKA DEPS...
#include <cmocka.h>

#include "status.h"
#include <stdio.h>
static void test_handle_status_invalid() {
    assert_null(handle_status(1));
}

static void test_handle_status_enum() {
    assert_string_equal(handle_status(OK), "HTTP/1.0 200 OK\r\n");
    assert_string_equal(handle_status(NOT_FOUND), "HTTP/1.0 404 Not Found\r\n");
}

static void test_handle_status_num() {
    assert_string_equal(handle_status(200), "HTTP/1.0 200 OK\r\n");
    assert_string_equal(handle_status(404), "HTTP/1.0 404 Not Found\r\n");
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_handle_status_invalid),
        cmocka_unit_test(test_handle_status_num),
        cmocka_unit_test(test_handle_status_enum),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
