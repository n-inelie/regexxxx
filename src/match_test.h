#pragma once

struct sample {
    char *text;
    bool expected_match;
};

void test_match_regex_single_char_plus(void);
void test_match_regex_single_char_fixed(void);
void test_match_regex_triple_concat_with_kleen_star(void);
