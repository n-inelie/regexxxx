#pragma once

struct sample {
    char *text;
    bool expected_match;
};

void test_match_regex_single_char_plus(void);
