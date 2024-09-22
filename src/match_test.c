#include "match_test.h"
#include "match.h"
#include "utils.h"

#include <stdint.h>
#include <stdio.h>

void test_match_regex_single_char_plus(void) {
    printf("Test: " ANSI_COLOR_CYAN "%s\n" ANSI_COLOR_RESET, __func__);
    printf("Regex: " ANSI_COLOR_MAGENTA "a+\n" ANSI_COLOR_RESET);

    Group *root = group_create(GROUP_CONCAT, 1, 1);
    group_append_item_symbol(root, symbol_create('a', 1, SIZE_MAX));

    struct sample samples[] = {
        {"b", false},
        {"a", true},
        {"aaaa", true},
        {"acba", false},
    };

    printf(ANSI_COLOR_YELLOW "Samples Report\n" ANSI_COLOR_RESET);
    struct sample sample;
    bool match;
    bool success = true;

    for (size_t i = 0; i < 4; ++i) {
        sample = samples[i];
        match = group_match(root, sample.text);

        printf("%s\tExpected: %s\tActual: %s\n", sample.text,
               BOOL_TO_STR(sample.expected_match), BOOL_TO_STR(match));

        if (match != sample.expected_match) {
            success = false;
        }
    }

    if (success) {
        printf(ANSI_COLOR_GREEN "SUCCESS\n" ANSI_COLOR_RESET);
    } else {
        printf(ANSI_COLOR_RED "FAILED\n" ANSI_COLOR_RESET);
    }

    group_destroy(root);
}
