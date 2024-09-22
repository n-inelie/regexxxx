#include "match_test.h"

int main(void) {
    test_match_regex_single_char_plus();
    test_match_regex_single_char_fixed();
    test_match_regex_triple_concat_with_kleen_star();
    return 0;
}
