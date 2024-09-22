#include "match.h"

#include <stdbool.h>

bool group_match(Group *g, char *text) {
    Symbol *s;
    size_t text_i = 0;

    for (size_t i = 0; i < g->item_count; ++i) {
        struct group_item item = g->items[i];
        switch (item.type) {
        case ITEM_SYMBOL:
            s = item.s;
            while (text[text_i] == s->c) {
                text_i++;
                s->count++;
                if (s->count == s->max) {
                    break;
                }
            }
            if (s->count < s->min) {
                return false;
            }
            break;
        case ITEM_SUB_GROUP:
            break;
        }
    }
    if (text[text_i] == '\0') {
        return true;
    }
    return false;
}
