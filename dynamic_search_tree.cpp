#include "dynamic_search_tree.h"

co_dynamic_serach_tree::co_dynamic_serach_tree() {
    setup(&this->list);
    this->tree = new CO_static_search_tree(16);
}

co_dynamic_serach_tree::~co_dynamic_serach_tree() {
    free(this->list.items);
}

void co_dynamic_serach_tree::add(int value) {
    int index = this->tree->get(value);
    insert(&this->list, index, value);
    this->tree->range_update(this->list.index, this->list.index + this->list.len, this->list.items);
}

int co_dynamic_serach_tree::get_successor(int value) {
    int index = this->tree->get(value);
    return this->list.items[index];
}