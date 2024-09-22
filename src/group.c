#include "group.h"

#include <assert.h>
#include <stdio.h>
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
    free(g->anchors);
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

void group_append_item_sub_group(Group *super, Group *sub) {
    struct group_item *temp = realloc(
        super->items, sizeof(struct group_item) * (super->item_count + 1));
    assert(temp != NULL);

    super->items = temp;
    super->items[super->item_count].sub_group = sub;
    super->items[super->item_count].type = ITEM_SUB_GROUP;
    super->item_count++;

    if (sub->min != 0) {
        size_t *anchor_temp =
            realloc(super->anchors, sizeof(size_t) * (super->anchor_count + 1));
        assert(anchor_temp != NULL);

        super->anchors = anchor_temp;
        super->anchors[super->anchor_count++] = super->item_count - 1;
    }
}

void group_append_item_symbol(Group *super, Symbol *s) {
    struct group_item *temp = realloc(
        super->items, sizeof(struct group_item) * (super->item_count + 1));
    assert(temp != NULL);

    super->items = temp;
    super->items[super->item_count].s = s;
    super->items[super->item_count].type = ITEM_SYMBOL;
    super->item_count++;

    if (s->min != 0) {
        size_t *anchor_temp =
            realloc(super->anchors, sizeof(size_t) * (super->anchor_count + 1));
        assert(anchor_temp != NULL);

        super->anchors = anchor_temp;
        super->anchors[super->anchor_count++] = super->item_count - 1;
    }
}
