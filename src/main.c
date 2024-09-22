#include "group.h"
#include "utils.h"

#include <stdint.h>
#include <stdio.h>

int main(void) {
    printf(ANSI_COLOR_MAGENTA "hello, world\n" ANSI_COLOR_RESET);

    // hardcoded group for regex `a|b*c`

    Group *root = group_create(GROUP_CONCAT, 1, 1);

    Group *g_0 = group_create(GROUP_UNION, 1, 1);
    group_append_item_sub_group(root, g_0);

    group_append_item_symbol(g_0, symbol_create('a', 1, 1));

    Group *g_0_1 = group_create(GROUP_CONCAT, 1, 1);
    group_append_item_sub_group(g_0, g_0_1);

    group_append_item_symbol(g_0_1, symbol_create('b', 0, SIZE_MAX));
    group_append_item_symbol(g_0_1, symbol_create('c', 1, 1));

    group_destroy(root);
    return 0;
}
