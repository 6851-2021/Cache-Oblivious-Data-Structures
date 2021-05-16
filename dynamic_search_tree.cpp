#include "dynamic_search_tree.h"

co_dynamic_serach_tree::co_dynamic_serach_tree() {
    setup(&this->list);
    this->N = this->list.N;
    this->tree = new co_static_search_tree(this->N);
}

co_dynamic_serach_tree::~co_dynamic_serach_tree() {
    free(this->list.items);
}


void co_dynamic_serach_tree::add(int value) {
    int index = this->tree->get(value);
    if(index == -1 )
        index = this->list.N - 1;

    int current_length = this->list.N;
    insert(&this->list, index, value);

    if (current_length != this->list.N)
    { //OFM resized
        this->N = this->list.N;
        delete (this->tree);
        this->tree = new co_static_search_tree(this->N);
        this->tree->range_update(0, this->N - 1, this->list.items);
    }
    else
    {
        this->tree->range_update(this->list.min_index, this->list.max_index, this->list.items);
    }
    
}

int co_dynamic_serach_tree::get_successor(int value) {
    int index = this->tree->get(value);
    if(index == -1) {
        return index;
    }
    return this->list.items[index];
}