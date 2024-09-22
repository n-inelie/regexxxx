#include "match_test.h"
#include "match.h"
#include "utils.h"

#include <stdint.h>
#include <stdio.h>

#define TEST_MATCH_DEFAULT_MESSAGE(regex)                                      \
    printf("Test: " ANSI_COLOR_CYAN "%s\n" ANSI_COLOR_RESET, __func__);        \
    printf("Regex: " ANSI_COLOR_MAGENTA "%s\n" ANSI_COLOR_RESET, regex)

#define SAMPLES_REPORT(sample_count)                                           \
    do {                                                                       \
        printf(ANSI_COLOR_YELLOW "Samples Report\n" ANSI_COLOR_RESET);         \
        struct sample sample;                                                  \
        bool match;                                                            \
        bool success = true;                                                   \
                                                                               \
        for (size_t i = 0; i < sample_count; ++i) {                            \
            sample = samples[i];                                               \
            match = group_match(root, sample.text);                            \
            if (match != sample.expected_match) {                              \
                success = false;                                               \
                                                                               \
                printf(ANSI_COLOR_RED                                          \
                       "%s\tExpected: %s\tActual: %s\n" ANSI_COLOR_RESET,      \
                       sample.text, BOOL_TO_STR(sample.expected_match),        \
                       BOOL_TO_STR(match));                                    \
                continue;                                                      \
            }                                                                  \
            printf("%s\t" ANSI_COLOR_YELLOW "Expected:" ANSI_COLOR_RESET       \
                   " %s\t" ANSI_COLOR_YELLOW "Actual:" ANSI_COLOR_RESET        \
                   " %s\n",                                                    \
                   sample.text, BOOL_TO_STR(sample.expected_match),            \
                   BOOL_TO_STR(match));                                        \
        }                                                                      \
                                                                               \
        if (success) {                                                         \
            printf(ANSI_COLOR_GREEN "SUCCESS\n" ANSI_COLOR_RESET);             \
        } else {                                                               \
            printf(ANSI_COLOR_RED "FAILED\n" ANSI_COLOR_RESET);                \
        }                                                                      \
    } while (0)

void test_match_regex_single_char_plus(void) {
    TEST_MATCH_DEFAULT_MESSAGE("a+");

    Group *root = group_create(GROUP_CONCAT, 1, 1);
    group_append_item_symbol(root, symbol_create('a', 1, SIZE_MAX));

    struct sample samples[] = {
        {"b", false},
        {"a", true},
        {"aaaa", true},
        {"acba", false},
    };

    SAMPLES_REPORT(4);

    group_destroy(root);
}

void test_match_regex_single_char_fixed(void) {
    TEST_MATCH_DEFAULT_MESSAGE("a{3, 5}");

    Group *root = group_create(GROUP_CONCAT, 1, 1);
    group_append_item_symbol(root, symbol_create('a', 3, 5));

    struct sample samples[] = {
        {"a", false},    {"aa", false},     {"aaa", true},    {"aaaa", true},
        {"aaaaa", true}, {"aaaaaa", false}, {"aaaba", false}, {"baaa", false},
    };

    SAMPLES_REPORT(8);

    group_destroy(root);
}
