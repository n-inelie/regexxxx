#include "group.h"

#include <assert.h>
#include <stdlib.h>

Group *group_create(const enum group_type type, const size_t min,
                    const size_t max) {
    Group *g = malloc(sizeof(*g));
    assert(g != NULL);

    g->type = type;
    g->items = NULL;
    g->item_count = 0;
    g->anchors = NULL;
    g->anchor_count = 0;
    g->count = 0;
    g->min = min;
    g->max = max;

    return g;
}

void group_destroy(Group *g) {
    for (size_t i = 0; i < g->item_count; ++i) {
        if (g->items->type == ITEM_SUB_GROUP) {
            free(g->items[i].sub_group);
        } else {
            free(g->items[i].s);
        }
    }
    for (size_t i = 0; i < g->anchor_count; ++i) {
        free(g->anchors);
    }
    free(g);
}

Symbol *symbol_create(const unsigned char c, const size_t min,
                      const size_t max) {
    Symbol *s = malloc(sizeof(*s));
    assert(s != NULL);

    s->c = c;
    s->count = 0;
    s->min = min;
    s->max = max;

    return s;
}
