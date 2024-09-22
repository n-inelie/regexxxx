#pragma once

#include <stddef.h>

typedef struct {
    unsigned char c;

    size_t count;
    size_t min;
    size_t max;
} Symbol;

typedef struct group {
    enum group_type {
        GROUP_CONCAT,
        GROUP_UNION,
    } type;

    struct group_item {
        union {
            struct group *sub_group;
            Symbol *s;
        };
        enum item_type {
            ITEM_SUB_GROUP,
            ITEM_SYMBOL,
        } type;
    } *items;
    size_t item_count;

    size_t *anchors;
    size_t anchor_count;

    size_t count;
    size_t min;
    size_t max;
} Group;

Symbol *symbol_create(const unsigned char c, const size_t min,
                      const size_t max);

Group *group_create(const enum group_type type, const size_t min,
                    const size_t max);
void group_destroy(Group *g);

void group_append_item_sub_group(Group *super, Group *sub);
void group_append_item_symbol(Group *super, Symbol *s);
