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

#include "dict.h"

void fn(context *ctx) {
    (void)ctx;
};

/* A test case that does nothing and succeeds. */
static void null_test_success() {
    assert_false(0);
}

static void test_size_dict_new(void **state) {
    dict_t dict = *state;

    assert_non_null(dict);
    assert_int_equal(sizeof(dict), 8);
    assert_int_equal(sizeof(*dict), 16);
}

static void test_dict_add_find(void **state) {
    dict_t dict = *state;
    uint32_t len = dict->len;

    // compiler should warn here. `-Wint-conversion`
    dict_add(dict, "foo", 2131);
    dict_add(dict, "bar", fn);

    assert_int_equal(dict->len - len, 2);

    assert_int_equal(dict_find_index(dict, "foo"), 0);
    assert_int_equal(dict_find_index(dict, "nope"), -1);
    assert_int_equal(dict_find_index(dict, "bar"), 1);

    assert_int_equal(dict_find(dict, "foo"), 2131);
    assert_int_equal(dict_find(dict, "bar"), fn);

    context *ctx;

    dict_find(dict, "bar")(ctx);
}

static int setup(void **state) {
    dict_t *dict = dict_new();
    *state = dict;

    if (!dict)
        return -1;

    return 0;
}

static int teardown(void **state) {
    dict_t dict = *state;

    assert_int_equal(sizeof(dict), 8);
    assert_int_equal(sizeof(*dict), 16);
    assert_int_equal(dict->len, 2);

    dict_free(dict);

    assert_int_equal(sizeof(dict), 8);
    assert_int_equal(sizeof(*dict), 16);
    assert_int_not_equal(dict->len, 2);

    return 0;
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(null_test_success),
        cmocka_unit_test(test_size_dict_new),
        cmocka_unit_test(test_dict_add_find),
    };

    return cmocka_run_group_tests(tests, setup, teardown);
}
