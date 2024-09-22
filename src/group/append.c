#include "group.h"

#include <assert.h>
#include <stdlib.h>

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
